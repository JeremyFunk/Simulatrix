#include "simixpch.h"
#include <Simulatrix/Core/Window.h>

#ifdef SIMIX_PLATFORM_WINDOWS
	#include <Simulatrix/Platform/Windows/WindowsWindow.h>
#endif

namespace Simulatrix {

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef SIMIX_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			SIMIX_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}