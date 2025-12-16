#include "pch.h"
#include "WaveDataIngestor.h"
#include "PCMConverter.h"

using namespace Syn;

WaveDataIngestor::WaveDataIngestor() {
	Format = SourceWaveFormat::Unknown;
	Channels = 1;
}

void WaveDataIngestor::ParseFormat(WAVEFORMATEX *wf) {
	if (wf->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
		WAVEFORMATEXTENSIBLE *wfx = reinterpret_cast<WAVEFORMATEXTENSIBLE*>(wf);
		const WORD bits = wfx->Samples.wValidBitsPerSample;
		if (IsEqualGUID(wfx->SubFormat, KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) && bits == 32) {
			Format = SourceWaveFormat::Float;
		}
		else if (IsEqualGUID(wfx->SubFormat, KSDATAFORMAT_SUBTYPE_PCM)) {
			if (bits == 16) Format = SourceWaveFormat::PCM16;
			else if (bits == 24) Format = SourceWaveFormat::PCM24;
			else if (bits == 32) Format = SourceWaveFormat::PCM32;
		}
	}
	else if (wf->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
		Format = SourceWaveFormat::Float;
	}
	else if (wf->wFormatTag == WAVE_FORMAT_PCM) {
		if (wf->wBitsPerSample == 16) Format = SourceWaveFormat::PCM16;
		else if (wf->wBitsPerSample == 24) Format = SourceWaveFormat::PCM24;
		else if (wf->wBitsPerSample == 32) Format = SourceWaveFormat::PCM32;
	}
	Channels = wf->nChannels;
}

void WaveDataIngestor::Ingest(BYTE *data, UINT32 count, DWORD flags, float *const outBuffer, size_t outBufferSize) {

	if (flags & AUDCLNT_BUFFERFLAGS_SILENT) {
		for (size_t i = 0; i < count && i < outBufferSize; i++) {
			outBuffer[i] = 0.0f;
		}
		return;
	}

	WaveData wd{ data, count, flags, outBuffer, outBufferSize };
	if (Format == SourceWaveFormat::Float) {
		IngestFloat(&wd);
	}
	else if (Format == SourceWaveFormat::PCM16) {
		IngestPCM16(&wd);
	}
	else if (Format == SourceWaveFormat::PCM24) {
		IngestPCM24(&wd);
	}
	else if (Format == SourceWaveFormat::PCM32) {
		IngestPCM32(&wd);
	}
}

void WaveDataIngestor::IngestFloat(WaveData *const data) const {
	float *samples = reinterpret_cast<float *>(data->InData);
	for (size_t sampleCursor = 0; sampleCursor < data->FrameCount; sampleCursor+=Channels) {
		float sum = 0;
		for (size_t channelIndex = 0; channelIndex < Channels; channelIndex++) {
			sum += samples[sampleCursor + channelIndex];
		}
		WriteToOutput(sum / (float)Channels, sampleCursor / Channels, data);
	}
}

void WaveDataIngestor::IngestPCM16(WaveData *const data) const {
	int16_t *samples = reinterpret_cast<int16_t *>(data->InData);
	for (size_t sampleCursor = 0; sampleCursor < data->FrameCount; sampleCursor += Channels) {
		float sum = 0;
		for (size_t channelIndex = 0; channelIndex < Channels; channelIndex++) {
			sum += UpcastPCM16(samples[sampleCursor + channelIndex]);
		}
		WriteToOutput(sum / (float)Channels, sampleCursor / Channels, data);
	}
}

void WaveDataIngestor::IngestPCM24(WaveData *const data) const {
	uint8_t *samples = reinterpret_cast<uint8_t *>(data->InData);
	// 24 bit samples downcast to 8 bit samples means three
	// data points per channel
	for (size_t sampleCursor = 0; sampleCursor < data->FrameCount * 3; sampleCursor += Channels*3) {
		float sum = 0;
		for (size_t channelIndex = 0; channelIndex < Channels; channelIndex++) {
			size_t frameStartIndex = sampleCursor + channelIndex * 3;
			sum += UpcastPCM24(samples[frameStartIndex], samples[frameStartIndex + 1], samples[frameStartIndex + 2]);
		}
		WriteToOutput(sum / (float)Channels, sampleCursor / 3 / Channels, data);
	}
}

void WaveDataIngestor::IngestPCM32(WaveData *const data) const {
	int32_t *samples = reinterpret_cast<int32_t *>(data->InData);
	for (size_t sampleCursor = 0; sampleCursor < data->FrameCount; sampleCursor += Channels) {
		float sum = 0;
		for (size_t channelIndex = 0; channelIndex < Channels; channelIndex++) {
			sum += UpcastPCM32(samples[sampleCursor + channelIndex]);
		}
		WriteToOutput(sum / (float)Channels, sampleCursor / Channels, data);
	}
}

void WaveDataIngestor::WriteToOutput(float value, size_t index, WaveData *const data) const {
	if (index < data->OutBufferSize) {
		data->OutBuffer[index] = value;
	}
}