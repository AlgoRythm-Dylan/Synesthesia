#pragma once

#ifdef _DEBUG
#define SYN_EXPORT_DEBUG __declspec(dllexport)
#else
#define SYN_EXPORT_DEBUG
#endif

#define SYN_EXPORT __declspec(dllexport)