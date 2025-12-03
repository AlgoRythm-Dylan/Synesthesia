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