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

    include "Simulatrix/vendor/GLFW"
    include "Simulatrix/vendor/Glad"
    include "Simulatrix/vendor/imgui"

project "Simulatrix"
    location "Simulatrix"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "simixpch.h"
    pchsource "Simulatrix/src/simixpch.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links{
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.19041.0"

        defines{
            "SIMIX_PLATFORM_WINDOWS",
            "SIMIX_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands{
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "SIMIX_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "SIMIX_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "SIMIX_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "Simulatrix/vendor/spdlog/include",
        "Simulatrix/src"
    }

    links {
        "Simulatrix"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.19041.0"

        defines{
            "SIMIX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SIMIX_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "SIMIX_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "SIMIX_DIST"
        buildoptions "/MD"
        optimize "On"