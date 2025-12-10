#include "pch.h"
#include "WaveDataIngestor.h"

using namespace Syn;

WaveDataIngestor::WaveDataIngestor() {
	format = SourceWaveFormat::Unknown;
}

void WaveDataIngestor::ParseFormat(WAVEFORMATEX *wf) {
	if (wf->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
		WAVEFORMATEXTENSIBLE *wfx = reinterpret_cast<WAVEFORMATEXTENSIBLE*>(wf);
		const WORD bits = wfx->Samples.wValidBitsPerSample;
		if (IsEqualGUID(wfx->SubFormat, KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) && bits == 32) {
			format = SourceWaveFormat::Float;
		}
		else if (IsEqualGUID(wfx->SubFormat, KSDATAFORMAT_SUBTYPE_PCM)) {
			if (bits == 16) format = SourceWaveFormat::PCM16;
			else if (bits == 24) format = SourceWaveFormat::PCM24;
			else if (bits == 32) format = SourceWaveFormat::PCM32;
		}
	}
	else if (wf->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
		format = SourceWaveFormat::Float;
	}
	else if (wf->wFormatTag == WAVE_FORMAT_PCM) {
		if (wf->wBitsPerSample == 16) format = SourceWaveFormat::PCM16;
		else if (wf->wBitsPerSample == 24) format = SourceWaveFormat::PCM24;
		else if (wf->wBitsPerSample == 32) format = SourceWaveFormat::PCM32;
	}
}

void WaveDataIngestor::Ingest(BYTE *data, UINT32 count, DWORD flags, float const *outBuffer, size_t outBufferSize) {
	if (format == SourceWaveFormat::Float) {

	}
}

void WaveDataIngestor::IngestFloat(BYTE *data, UINT32 count, DWORD flags, float const *outBuffer, size_t outBufferSize) {

}