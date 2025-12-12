#pragma once

#include <Audioclient.h>

#include "SourceWaveFormat.h"

namespace Syn {

	struct WaveData {
		BYTE *InData;
		UINT32 FrameCount;
		DWORD Flags;
		float *OutBuffer;
		size_t OutBufferSize;
	};

	struct WaveDataIngestor
	{
		WaveDataIngestor();
		SourceWaveFormat format;
		void ParseFormat(WAVEFORMATEX*);
		void Ingest(BYTE *, UINT32, DWORD, float *const, size_t);
	private:
		void IngestFloat(WaveData *const) const;
	};
}
