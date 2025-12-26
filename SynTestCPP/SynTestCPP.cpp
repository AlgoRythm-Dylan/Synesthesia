#include "pch.h"
#include "CppUnitTest.h"

#include "TestSignalGenerator.h"
#include "Fourier.h"
#include "ButterflyTranslator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr float TOLERANCE = 1e-6;
constexpr double TOLERANCE_DOUBLE_PRECISION = 1e-9;

namespace SynTestCPP
{
	TEST_CLASS(SynTestCPP)
	{
	public:

		TEST_METHOD(Butterflies)
		{
			auto butterflies = Syn::computeButterflies(2048);
			Assert::AreEqual(static_cast<size_t>(0), butterflies[0]);
			delete butterflies;
		}

		TEST_METHOD(FFTOneFrequency)
		{
			TestSignalGenerator generator;
			generator.Add(1, 3.5);
			Syn::Fourier transform(2048);
			for (size_t i = 0; i < 2048; i++) {
				transform.AddSample(generator.Next());
			}
			float *outputBuffer = new float[2048];
			transform.Transform(outputBuffer);
			Assert::AreEqual(3.5f, outputBuffer[0], TOLERANCE);
		}

	};
}
