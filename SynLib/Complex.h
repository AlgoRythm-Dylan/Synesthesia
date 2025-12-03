#pragma once

namespace Syn {

	struct Complex
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
