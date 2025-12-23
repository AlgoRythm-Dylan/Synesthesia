#include "pch.h"
#include "TestSignalGenerator.h"

#include <cmath>

constexpr double PI = 3.14159265358979323846;
constexpr double TAU = 2 * PI;

TestSignalFrequency::TestSignalFrequency() {
	Frequency = 1;
	Amplitude = 1;
	Phase = 0;
}

TestSignalFrequency::TestSignalFrequency(double freq, double amp) {
	Frequency = freq;
	Amplitude = amp;
	Phase = 0;
}

double TestSignalFrequency::GetValueAtTime(double time) const {
	return cos(TAU * Frequency * time + Phase) * Amplitude;
}

TestSignalGenerator::TestSignalGenerator() {
	SamplesPerSecond = 2;
	m_clock = 0;
	m_frequencyCount = 0;
}

double TestSignalGenerator::Next() {
	double sum = 0;
	double time = Time();
	for (size_t i = 0; i < m_frequencyCount; i++) {
		sum += m_frequencies[i].GetValueAtTime(time);
	}
	m_clock++;
	return sum;
}

double TestSignalGenerator::Time() const {
	return (double)m_clock / (double)SamplesPerSecond;
}

TestSignalFrequency *TestSignalGenerator::Add(double freq, double amp) {
	return new (&m_frequencies[m_frequencyCount++]) TestSignalFrequency(freq, amp);
}

void TestSignalGenerator::UseNyquist() {
	SamplesPerSecond = 2.0f * HighestFrequency();
}

double TestSignalGenerator::HighestFrequency() const {
	if (m_frequencyCount == 0) {
		return 0;
	}
	double highestFrequency = m_frequencies[0].Frequency;
	for (size_t i = 1; i < m_frequencyCount; i++) {
		if (m_frequencies[i].Frequency > highestFrequency) {
			highestFrequency = m_frequencies[i].Frequency;
		}
	}
	return highestFrequency;
}
