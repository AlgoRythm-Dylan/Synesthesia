#include "pch.h"
#include "WinAudio.h"

using namespace Syn;

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

	client->GetMixFormat(&format);
	client->Initialize(
		AUDCLNT_SHAREMODE_SHARED,
		AUDCLNT_STREAMFLAGS_LOOPBACK,
		350000, // Buffer window time in 100s of nanoseconds... 35ms
		0,
		format,
		NULL
	);
	client->GetService(__uuidof(IAudioCaptureClient), (void**)&capture);
	client->Start();
}