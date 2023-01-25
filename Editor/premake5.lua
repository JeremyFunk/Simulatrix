project "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Simulatrix/vendor/spdlog/include",
		"%{wks.location}/Simulatrix/src",
		"%{wks.location}/Simulatrix/vendor",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.ReactPhysics3D}"
	}

	links
	{
		"Simulatrix"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "SIMIX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SIMIX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SIMIX_DIST"
		runtime "Release"
		optimize "on"