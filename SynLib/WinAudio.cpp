#include "pch.h"
#include "WinAudio.h"

using namespace Syn;

WinAudio::WinAudio() {
	m_format = nullptr;
	client = nullptr;
	capture = nullptr;
}

void WinAudio::Initialize() {
	auto result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(result)) {
		throw std::runtime_error("Failed to initialize COM session");
	}

	deviceContainer.Initialize();

	deviceContainer.device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&client);
	if (client == nullptr) {
		throw std::runtime_error("Failed to get audio client");
	}

	client->GetMixFormat(&m_format);
	wdi.ParseFormat(m_format);

	client->Initialize(
		AUDCLNT_SHAREMODE_SHARED,
		AUDCLNT_STREAMFLAGS_LOOPBACK,
		350000, // Buffer window time in 100s of nanoseconds... 35ms
		0,
		m_format,
		NULL
	);
	client->GetService(__uuidof(IAudioCaptureClient), (void**)&capture);
	client->Start();
}

void WinAudio::ParseWaveFormat() {
	m_sourceFormat = SourceWaveFormat::Unknown;

	if (m_formatEX != nullptr) {
		const GUID& sub = m_formatEX->SubFormat;
		WORD bits = m_formatEX->Samples.wValidBitsPerSample;

		if (IsEqualGUID(sub, KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) && bits == 32) {
			m_sourceFormat = SourceWaveFormat::Float;
		}
		else if (IsEqualGUID(sub, KSDATAFORMAT_SUBTYPE_PCM)) {
			if (bits == 16) m_sourceFormat = SourceWaveFormat::PCM16;
			if (bits == 24) m_sourceFormat = SourceWaveFormat::PCM24;
			if (bits == 32) m_sourceFormat = SourceWaveFormat::PCM32;
		}

	}
	else if (m_format->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
		m_sourceFormat = SourceWaveFormat::Float;
	}
	else if (m_format->wFormatTag == WAVE_FORMAT_PCM) {
		if (m_format->wBitsPerSample == 16) m_sourceFormat = SourceWaveFormat::PCM16;
		else if (m_format->wBitsPerSample == 24) m_sourceFormat = SourceWaveFormat::PCM24;
		else if (m_format->wBitsPerSample == 32) m_sourceFormat = SourceWaveFormat::PCM32;
	}
}

size_t WinAudio::Read(float const *outBuffer, size_t outBufferSize) {
	BYTE* data;
	UINT32 count;
	DWORD flags;
	capture->GetBuffer(&data, &count, &flags, NULL, NULL);
	wdi.Ingest(data, count, flags, outBuffer, outBufferSize);
	capture->ReleaseBuffer(count);
	return static_cast<size_t>(count);
}

void WinAudio::Release() {
	if (m_format != nullptr) {
		CoTaskMemFree(m_format);
		m_format = nullptr;
	}
	if (capture != nullptr) {
		capture->Release();
		capture = nullptr;
	}
	if (client != nullptr) {
		client->Stop();
		client = nullptr;
	}
}

WinAudio::~WinAudio() {
	Release();
}