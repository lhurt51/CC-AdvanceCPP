#pragma once

// enabling the asserts
#ifdef GE_DEBUG
	#define GE_ENABLE_ASSERTS
#endif

// Assert define to disable the asserts on release
#ifdef GE_ENABLE_ASSERTS
	#define GE_ASSERT(x, ...) { if (!(x)) { std::cerr << "Assertion Failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }
	#define GE_CORE_ASSERT(x, ...) { if (!(x)) { std::cerr << "Assertion Failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }
#else
	#define GE_ASSERT(x, ...)
	#define GE_CORE_ASSERT(x, ...)
#endif

// Bit mask
#define BIT(x) (1 << x)
// Define for binding method functions
#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)