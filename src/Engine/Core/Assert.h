#pragma once


#include "Engine/Core/Base.h"
#include "Engine/Core/Logger.h"
#include <filesystem>

#ifdef SHELL_ENABLE_ASSERTS

    // Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define SHELL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { SHELL##type##ERROR(msg, __VA_ARGS__); SHELL_DEBUGBREAK(); } }
	#define SHELL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) SHELL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define SHELL_INTERNAL_ASSERT_NO_MSG(type, check) SHELL_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SHELL_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define SHELL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define SHELL_INTERNAL_ASSERT_GET_MACRO(...) SHELL_EXPAND_MACRO( SHELL_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SHELL_INTERNAL_ASSERT_WITH_MSG, SHELL_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define SHELL_ASSERT(...) SHELL_EXPAND_MACRO( SHELL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define SHELL_CORE_ASSERT(...) SHELL_EXPAND_MACRO( SHELL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define SHELL_ASSERT(...)
#define SHELL_CORE_ASSERT(...)
#endif