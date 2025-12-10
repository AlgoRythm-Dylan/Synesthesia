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