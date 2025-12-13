#pragma once

namespace Syn {
	constexpr static float UpcastPCM16(int16_t);
	constexpr static float UpcastPCM24(uint8_t, uint8_t, uint8_t);
	constexpr static float UpcastPCM32(int32_t);
}
