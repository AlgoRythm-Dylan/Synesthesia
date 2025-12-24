#pragma once

#include "WinAudio.h"
#include "Fourier.h"
#include "ExportSymbols.h"

static Syn::WinAudio *g_syn_audio = nullptr;
static Syn::Fourier *g_syn_transform = nullptr;
static float *g_syn_sampleBuffer = nullptr;
static size_t g_syn_sampleBufferCount, g_syn_sampleBufferSize;

extern "C" {
	SYN_EXPORT void SynBegin(size_t bufferSize);
	SYN_EXPORT void SynUpdate(float *);
	SYN_EXPORT void SynEnd();
}