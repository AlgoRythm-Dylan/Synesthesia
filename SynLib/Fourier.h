#pragma once

#include "Complex.h"
#include "CircularBuffer.hpp"

namespace Syn {
	struct Fourier
	{
		Fourier(size_t size);
		~Fourier();
		void AddSample(float const sample);
		void Transform(float *const outputBuffer);
	private:
		const size_t m_size;
		const Complex *m_twiddles;
		Complex *m_workBuffer;
		CircularBuffer<float> *m_samples;
		const size_t* m_butterflies;
		inline const Complex& Twiddle(size_t const index) const {
			return m_twiddles[index];
		}

		void SetupWorkBuffer(float *const outputBuffer);
	};
}
