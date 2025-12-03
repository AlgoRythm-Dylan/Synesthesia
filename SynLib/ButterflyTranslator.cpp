#include "pch.h"
#include "ButterflyTranslator.h"

namespace Syn {

	constexpr size_t reverseBits(size_t input, size_t nBits) {
		size_t rev = 0;
		for (size_t j = 0; j < nBits; j++) {
			rev <<= 1;              // make room for next bit
			rev |= (input & 1);     // copy least significant bit of i
			input >>= 1;            // shift i to get next bit
		}
		return rev;
	}

	size_t* computeButterflies(size_t bufferLength) {
		size_t* buffer = new size_t[bufferLength];
		const size_t bitCount = log2(bufferLength);
		for (size_t i = 1; i < bufferLength; i++) {
			buffer[i] = reverseBits(i, bitCount);
		}
		return buffer;
	}

}
