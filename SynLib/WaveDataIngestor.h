#pragma once

#include <Audioclient.h>

#include "SourceWaveFormat.h"
#include "ExportSymbols.h"

namespace Syn {

	struct SYN_EXPORT_DEBUG WaveData {
		BYTE *InData;
		UINT32 FrameCount;
		DWORD Flags;
		float *OutBuffer;
		size_t OutBufferSize;
	};

	struct SYN_EXPORT_DEBUG WaveDataIngestor
	{
		WaveDataIngestor();
		SourceWaveFormat Format;
		size_t Channels;
		void ParseFormat(WAVEFORMATEX*);
		void Ingest(BYTE *, UINT32, DWORD, float *const, size_t);
	private:
		void IngestFloat(WaveData *const) const;
		void IngestPCM16(WaveData *const) const;
		void IngestPCM24(WaveData *const) const;
		void IngestPCM32(WaveData *const) const;
		void WriteToOutput(float, size_t, WaveData *const) const;
	};
}
