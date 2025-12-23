#pragma once

namespace SynTest {
	struct TestSignalFrequency {
		double Frequency, Amplitude, Phase;
		TestSignalFrequency();
		TestSignalFrequency(double freq, double amp);
		double GetValueAtTime(double time) const;
	};

	enum SampleRate {
		SR_440 = 44100
	};

	struct TestSignalGenerator {
		unsigned long SamplesPerSecond;
		TestSignalGenerator();
		double Next();
		double Time() const;
		TestSignalFrequency *Add(double freq, double amp);
		void UseNyquist();
	private:
		size_t m_frequencyCount;
		TestSignalFrequency m_frequencies[32];
		unsigned long m_clock;
		double HighestFrequency() const;
	};
}