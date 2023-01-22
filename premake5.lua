include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Simulatrix"
	architecture "x86_64"
	startproject "Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}
	
	defines
	{
		"SIMIX_PLATFORM_WINDOWS",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Simulatrix/vendor/GLFW"
include "Simulatrix/vendor/Glad"
include "Simulatrix/vendor/ImGui"
include "Simulatrix/vendor/yaml-cpp"
include "Simulatrix"
include "Editor"
include "Sandbox"