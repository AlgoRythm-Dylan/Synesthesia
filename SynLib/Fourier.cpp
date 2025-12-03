#include "pch.h"
#include "Fourier.h"
#include "Twiddles.h"
#include "ButterflyTranslator.h"

using namespace Syn;

Fourier::Fourier(size_t size) : m_size(size), m_totalSteps(log2(size)) {
	m_twiddles = computeTwiddles(size / 2);
	m_workBuffer = new Complex[size];
	m_samples = new CircularBuffer<float>(size);
	m_butterflies = computeButterflies(size);
}

void Fourier::AddSample(float const sample) {
	m_samples->Add(sample);
}

size_t Fourier::OutputBufferSize() const {
	return (m_size / 2) + 1;
}

inline void Fourier::Transform(float* const outputBuffer) {
	SetupWorkBuffer(outputBuffer);
	for (size_t i = 1; i < m_totalSteps; i++) {
		ProcessWorkBuffer(i);
	}
	ProjectMagnitudes(outputBuffer);
}

inline void Fourier::SetupWorkBuffer(float* const outputBuffer) {
	for (size_t i = 0; i < m_size / 2; i++) {
		const size_t cursor = 2 * i;
		const float even = m_samples->Get(m_butterflies[cursor]);
		const float odd = m_samples->Get(m_butterflies[cursor + 1]);
		m_workBuffer[cursor].Real = even + odd;
		m_workBuffer[cursor].Imaginary = 0;
		m_workBuffer[cursor + 1].Real = even - odd;
		m_workBuffer[cursor + 1].Imaginary = 0;
	}
}

inline void Fourier::ProcessWorkBuffer(size_t const step) {
	const size_t span = static_cast<size_t>(1) << step;
	const size_t halfSpan = span / 2;
	const size_t sizeOverSpan = m_size / span;
	const size_t groupCount = m_size / span;
	for (size_t group = 0; group < groupCount; group++) {
		const size_t groupStart = span * group;
		
		for (size_t pairStart = groupStart; pairStart < groupStart + halfSpan; pairStart++) {
			const auto even = m_workBuffer[pairStart];
			const auto& odd = m_workBuffer[pairStart + halfSpan];
			const auto& twiddle = m_twiddles[(pairStart - groupStart) * sizeOverSpan];
			const auto twiddledOdd = twiddle * odd;

			m_workBuffer[pairStart] = even + twiddledOdd;
			m_workBuffer[pairStart + halfSpan] = even - twiddledOdd;
		}
	}
}

inline void Fourier::ProjectMagnitudes(float *const outputBuffer) {
	const auto limit = OutputBufferSize();
	for (size_t i = 0; i < limit; i++) {
		outputBuffer[i] = m_workBuffer[i].Magnitude();
	}
}

Fourier::~Fourier() {
	delete m_twiddles;
	delete m_workBuffer;
	delete m_samples;
	delete m_butterflies;
}