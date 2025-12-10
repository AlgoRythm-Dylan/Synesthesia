#pragma once

#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <atlcomcli.h>
#include <stdexcept>

#include "WaveDataIngestor.h"

namespace Syn {

    struct WinAudioDeviceContainer {
        CComPtr<IMMDeviceEnumerator> enumerator;
        CComPtr<IMMDevice> device;
        void Initialize() {
            auto result = enumerator.CoCreateInstance(__uuidof(MMDeviceEnumerator));
            if (FAILED(result)) {
                throw std::runtime_error("Failed to create MMDeviceEnumerator");
            }
            result = enumerator->GetDefaultAudioEndpoint(EDataFlow::eRender, ERole::eConsole, &device);
            if (FAILED(result)) {
                throw std::runtime_error("Failed to initialize default audio device");
            }
        }
    };

    struct WinAudio
    {
        WinAudioDeviceContainer deviceContainer;
        IAudioClient *client;
        IAudioCaptureClient *capture;

        WinAudio();
        ~WinAudio();

        void Initialize();
        void Release();
        size_t Read(float const*, size_t);
    private:
        WAVEFORMATEX* m_format;
        WaveDataIngestor wdi;
    };
}
