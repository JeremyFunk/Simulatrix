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
		"src/**.cpp",

		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/crude_json.h",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/crude_json.cpp",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_bezier_math.h",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_canvas.h",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_canvas.cpp",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_extra_math.h",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_node_editor.h",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_node_editor.cpp",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_node_editor_api.cpp",
		"%{wks.location}/Simulatrix/vendor/imgui-node-editor/imgui_node_editor_internal.h",

	}

	includedirs
	{
		"%{wks.location}/Simulatrix/vendor/spdlog/include",
		"%{wks.location}/Simulatrix/src",
		"%{wks.location}/Simulatrix/vendor",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.ReactPhysics3D}",
		"%{IncludeDir.imgui_node_editor}"
	}

	links
	{
		"Simulatrix"
	}

	filter "files:vendor/imgui-node-editor/**.cpp"
	flags { "NoPCH" }

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