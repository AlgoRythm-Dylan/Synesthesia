#pragma once

#include "ExportSymbols.h"

namespace Syn {
	SYN_EXPORT_DEBUG float UpcastPCM16(int16_t);
	SYN_EXPORT_DEBUG float UpcastPCM24(uint8_t, uint8_t, uint8_t);
	SYN_EXPORT_DEBUG float UpcastPCM32(int32_t);
}
