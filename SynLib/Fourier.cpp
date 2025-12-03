#include "pch.h"
#include "Fourier.h"
#include "Twiddles.h"
#include "ButterflyTranslator.h"

using namespace Syn;

Fourier::Fourier(size_t size) : m_size(size) {
	m_twiddles = computeTwiddles(size / 2);
	m_workBuffer = new Complex[size];
	m_samples = new CircularBuffer<float>(size);
	m_butterflies = computeButterflies(size);
}

void Fourier::AddSample(float const sample) {
	m_samples->Add(sample);
}

void Fourier::Transform(float* const outputBuffer) {
	SetupWorkBuffer(outputBuffer);
}

void Fourier::SetupWorkBuffer(float* const outputBuffer) {
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

Fourier::~Fourier() {
	delete m_twiddles;
	delete m_workBuffer;
	delete m_samples;
	delete m_butterflies;
}