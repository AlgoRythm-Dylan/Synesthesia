#include "pch.h"
#include "Exports.h"

#include <cassert>

void SynBegin(size_t bufferSize) {
	if (g_syn_transform == nullptr && g_syn_audio == nullptr && g_syn_sampleBuffer == nullptr) {
		g_syn_transform = new Syn::Fourier(bufferSize);
		g_syn_audio = new Syn::WinAudio();

		g_syn_audio->Initialize();

		g_syn_sampleBufferSize = bufferSize * 2;
		g_syn_sampleBuffer = new float[g_syn_sampleBufferSize];
	}
}

void SynUpdate(float* outBuffer) {
	assert(g_syn_sampleBuffer != nullptr);
	g_syn_sampleBufferCount = g_syn_audio->Read(g_syn_sampleBuffer, g_syn_sampleBufferSize);
	for (size_t i = 0; i < g_syn_sampleBufferCount; i++) {
		g_syn_transform->AddSample(g_syn_sampleBuffer[i]);
	}
	g_syn_transform->Transform(outBuffer);
}

void SynEnd() {
	if (g_syn_transform != nullptr) {
		delete g_syn_transform;
		g_syn_transform = nullptr;
	}
	if (g_syn_audio != nullptr) {
		delete g_syn_audio;
		g_syn_audio = nullptr;
	}
	if (g_syn_sampleBuffer != nullptr) {
		delete g_syn_sampleBuffer;
		g_syn_sampleBuffer = nullptr;
	}
}