#pragma once

#include <Audioclient.h>

#include "SourceWaveFormat.h"

namespace Syn {
	struct WaveDataIngestor
	{
		WaveDataIngestor();
		SourceWaveFormat format;
		void ParseFormat(WAVEFORMATEX*);
		void Ingest(BYTE *, UINT32, DWORD, float const *, size_t);
	};
}
