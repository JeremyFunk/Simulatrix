workspace "Simulatrix"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    IncludeDir = {}
    IncludeDir["GLFW"] = "Simulatrix/vendor/GLFW/include"
    IncludeDir["Glad"] = "Simulatrix/vendor/Glad/include"
    IncludeDir["ImGui"] = "Simulatrix/vendor/imgui"
    IncludeDir["GLM"] = "Simulatrix/vendor/glm"
    IncludeDir["entt"] = "Simulatrix/vendor/entt/include"
    IncludeDir["stbi"] = "Simulatrix/vendor/stbi_image"

    include "Simulatrix/vendor/GLFW"
    include "Simulatrix/vendor/Glad"
    include "Simulatrix/vendor/imgui"

project "Simulatrix"
    location "Simulatrix"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "simixpch.h"
    pchsource "Simulatrix/src/simixpch.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"Simulatrix/vendor/stbi_image/**.h",
		"Simulatrix/vendor/stbi_image/**.cpp"
    }

    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.stbi}"
    }

    defines 
    {
        _CRT_SECURE_NO_WARNINGS
    }

    
    links{
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
    
    filter "system:windows"
        systemversion "latest"

        defines{
            "SIMIX_PLATFORM_WINDOWS",
            "SIMIX_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "SIMIX_DEBUG"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "SIMIX_RELEASE"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "SIMIX_DIST"
        buildoptions "/MD"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "Simulatrix/vendor/spdlog/include",
        "Simulatrix/src",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.stbi}"
    }

    links {
        "Simulatrix"
    }
    
    filter "system:windows"
        systemversion "latest"

        defines{
            "SIMIX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SIMIX_DEBUG"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "SIMIX_RELEASE"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "SIMIX_DIST"
        buildoptions "/MD"
        optimize "on"