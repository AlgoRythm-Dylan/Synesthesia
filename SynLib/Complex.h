#pragma once

#include "ExportSymbols.h"

namespace Syn {

	struct SYN_EXPORT_DEBUG Complex
	{
		Complex();
		Complex(float, float);
		float Real, Imaginary;

		Complex operator *(const Complex& other) const;
		Complex operator +(const Complex& other) const;
		Complex operator -(const Complex& other) const;

		float Magnitude() const;
	};

}
