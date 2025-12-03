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
		inline size_t OutputBufferSize() const;
	private:
		const size_t m_size, m_totalSteps;
		const Complex *m_twiddles;
		Complex *m_workBuffer;
		CircularBuffer<float> *m_samples;
		const size_t* m_butterflies;
		inline const Complex& Twiddle(size_t const index) const {
			return m_twiddles[index];
		}

		inline void SetupWorkBuffer(float *const outputBuffer);
		inline void ProcessWorkBuffer(size_t step);
		inline void ProjectMagnitudes(float *const outputBuffer);
	};
}
