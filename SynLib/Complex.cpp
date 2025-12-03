#include "pch.h"
#include "Complex.h"

using namespace Syn;

Complex::Complex() {
	Real = 0;
	Imaginary = 0;
}

Complex::Complex(float real, float imaginary) {
	Real = real;
	Imaginary = imaginary;
}

Complex Complex::operator * (const Complex& other) const {
	return Complex(
		(Real * other.Real) - (Imaginary * other.Imaginary),
		(Real * other.Imaginary) + (Imaginary * other.Real)
	);
}

Complex Complex::operator + (const Complex& other) const {
	return Complex(
		Real + other.Real,
		Imaginary + other.Imaginary
	);
}

Complex Complex::operator - (const Complex& other) const {
	return Complex(
		Real - other.Real,
		Imaginary - other.Imaginary
	);
}

float Complex::Magnitude() const {
	return sqrtf((Real * Real) + (Imaginary * Imaginary));
}