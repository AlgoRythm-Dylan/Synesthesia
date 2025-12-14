#pragma once

#include "WinAudio.h"
#include "Fourier.h"

#define SYN_API __declspec(dllexport)

static Syn::WinAudio *g_syn_audio = nullptr;
static Syn::Fourier *g_syn_transform = nullptr;
static float *g_syn_sampleBuffer = nullptr;
static size_t g_syn_sampleBufferCount, g_syn_sampleBufferSize;

extern "C" {
	SYN_API void SynBegin(size_t bufferSize);
	SYN_API void SynUpdate(float *);
	SYN_API void SynEnd();
}