workspace "ConsolePacMan"
	architecture "x64"
	startproject "PacManRemake"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
-- IncludeDir = {}
-- IncludeDir["GLFW"] = "GhostEngine/vendor/GLFW/include"
-- IncludeDir["Glad"] = "GhostEngine/vendor/Glad/include"
-- IncludeDir["ImGui"] = "GhostEngine/vendor/imgui"
-- IncludeDir["Glm"] = "GhostEngine/vendor/glm"

-- group "Dependencies"
	-- include "GhostEngine/vendor/GLFW"
	-- include "GhostEngine/vendor/Glad"
	-- include "GhostEngine/vendor/imgui"
-- group ""

project "GameEngine"
	location "GameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "GameEngine/src/gepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
		-- "%{prj.name}/Vendor/glm/glm/**.hpp",
		-- "%{prj.name}/Vendor/glm/glm/**.inl"
	}
	
	defines
	{
	 	"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		--"%{prj.name}/Vendor/spdlog/include",
		--"%{IncludeDir.Glad}",
		--"%{IncludeDir.GLFW}",
		--"%{IncludeDir.ImGui}",
		--"%{IncludeDir.Glm}"
	}

	links
	{
		--"GLFW",
		--"Glad",
		--"ImGui",
		--"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "on"

project "PacManRemake"
	location "PacManRemake"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		--"GameEngine/vendor/spdlog/include",
		"GameEngine/src",
		--"GameEngine/vendor",
		--"%{IncludeDir.Glm}"
	}

	links
	{
		"GameEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "on"