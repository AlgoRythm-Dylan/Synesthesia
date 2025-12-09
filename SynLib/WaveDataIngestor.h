#pragma once

#include "SourceWaveFormat.h"

namespace Syn {
	struct WaveDataIngestor
	{
		WaveDataIngestor();
		SourceWaveFormat format;
		void ParseFormat(WAVEFORMATEX*);
	};
}
