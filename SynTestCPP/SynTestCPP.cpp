#include "pch.h"
#include "CppUnitTest.h"

#include "TestSignalGenerator.h"
#include "Fourier.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr float TEST_TOLERANCE = 1e-6;
constexpr double TEST_TOLERANCE_D = 1e-9;

namespace SynTestCPP
{
	TEST_CLASS(SynTestCPP)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			TestSignalGenerator generator;
			generator.Add(1, 3.5);
			Syn::Fourier transform(2048);
			for (size_t i = 0; i < 2048; i++) {
				transform.AddSample(generator.Next());
			}
			float *outputBuffer = new float[2048];
			transform.Transform(outputBuffer);
			Assert::AreEqual(3.5f, outputBuffer[0], TEST_TOLERANCE);
		}
	};
}
