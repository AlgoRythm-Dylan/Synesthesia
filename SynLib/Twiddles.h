#pragma once

#include "pch.h"
#include "Complex.h"

namespace Syn {

	constexpr float TAU = 6.2831853f;

	SYN_EXPORT_DEBUG Complex* computeTwiddles(size_t);

}
