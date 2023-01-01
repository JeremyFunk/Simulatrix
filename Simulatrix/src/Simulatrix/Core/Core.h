#pragma once

#ifdef SIMIX_PLATFORM_WINDOWS
    #ifdef SIMIX_BUILD_DLL
        #define SIMIX_API __declspec(dllexport)
    #else
        #define SIMIX_API __declspec(dllimport)
    #endif
#else
#error Only Windows supported!
#endif

#ifdef SIMIX_ENABLE_ASSERTS
    #define SIMIX_ASSERT(x, ...) {if(!(x)) {SIMIX_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
    #define SIMIX_CORE_ASSERT(x, ...) {if(!(x)) {SIMIX_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define SIMIX_ASSERT(x, ...)
#define SIMIX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}