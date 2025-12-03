#include "pch.h"
#include "Twiddles.h"

namespace Syn {

	Complex* computeTwiddles(size_t size) {
		auto array = new Complex[size];
		for (size_t counter = 0; counter < size; counter++) {
			const float angle = -TAU * static_cast<float>(counter) / static_cast<float>(size);
			array[counter] = Complex(cosf(angle), sinf(angle));
		}
		return array;
	}

}