#include "pch.h"
#include "PCMConverter.h"

namespace Syn {
	constexpr float Upcast16(uint16_t pcm) {
		// Divide by max value of 16 bit integer to get
		// float range between 0 and 1
		return pcm / 32786.0f;
	}

	constexpr float Upcast24(uint8_t a, uint8_t b, uint8_t c) {
		// int32_t upcastInt = (int32_t)(a | b << 8 | c << 16);
		// 
		// At this point, the 23rd bit is the sign bit. On a 32 bit
		// integer, that needs to be the 31st bit. Unfortunately,
		// this mean our int32 will never have a negative value (BAD!)
		// and any more siginificant bits will be incorrect 0s instead of
		// 1s (WORSE!) - junk data.
		//
		// Integers are stored in two's complement:
		// (negative numbers have their binary inverted
		// and have 1 added to them), so we need to
		// handle that TOO by checking if the PCM sample
		// was negative to start with, then
		// basically just filling in the extra 8
		// most significant bits with 1
		//
		// OR we can do some fancy shifting! Basically,
		// fill up the integer into the wrong side
		// Example:
		// CORRECT: 0abc
		// ALT:     abc0
		//
		// Then, shift THAT whole deal back 8 bits,
		// so the 0 will go away and the sign bit will
		// propagate
		int32_t upcastInt = (uint32_t)(a << 8 | b << 16 | c << 24) >> 8;
		// Normalize between 0 and 1 like the rest of the upcasts
		return upcastInt / 8388608.0f;
	}

	constexpr float Upcast32(uint32_t pcm) {
		return pcm / 2147483648.0f;
	}
}
