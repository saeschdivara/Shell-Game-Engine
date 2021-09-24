
#ifdef SHELL_APP_DEBUG
#if defined(SHELL_PLATFORM_WINDOWS)
		#define SHELL_DEBUGBREAK() __debugbreak()
	#elif defined(SHELL_PLATFORM_LINUX)
		#include <signal.h>
		#define SHELL_DEBUGBREAK() raise(SIGTRAP)
	#elif defined(SHELL_PLATFORM_MACOS)
		#include <csignal>
		#define SHELL_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define SHELL_ENABLE_ASSERTS
#else
#define SHELL_DEBUGBREAK()
#endif

#define SHELL_EXPAND_MACRO(x) x
#define SHELL_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)
#define SHELL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }