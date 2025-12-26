#include "pch.h"
#include "CppUnitTest.h"
#include "TestingSymbols.h"

#include "Complex.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SynTestCPP
{
	TEST_CLASS(SynTestComplex)
	{
	public:

		TEST_METHOD(AddComplex)
		{
			Syn::Complex a(1, 0);
			Syn::Complex b(2, 0);
			Syn::Complex c = a + b;
			Assert::AreEqual(3.0f, c.Real, TOLERANCE);
			Assert::AreEqual(0.0f, c.Imaginary, TOLERANCE);
		}

		TEST_METHOD(SubComplex)
		{
			Syn::Complex a(1, 0);
			Syn::Complex b(2, 0);
			Syn::Complex c = a - b;
			Assert::AreEqual(-1.0f, c.Real, TOLERANCE);
			Assert::AreEqual(0.0f, c.Imaginary, TOLERANCE);
		}

		TEST_METHOD(MultiplyComplex)
		{
			Syn::Complex a(1, 3);
			Syn::Complex b(2, 5);
			Syn::Complex c = a * b;
			Assert::AreEqual(-13.0f, c.Real, TOLERANCE);
			Assert::AreEqual(11.0f, c.Imaginary, TOLERANCE);
		}

		TEST_METHOD(ComplexMagnitude)
		{
			Syn::Complex a(5, 12);
			Assert::AreEqual(13.0f, a.Magnitude(), TOLERANCE);
		}

	};
}
