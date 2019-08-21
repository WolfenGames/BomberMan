workspace "Swallow"

	startproject "Bomberman"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directoies relative to root folder (solution directory)

	group "Dependencies"
		include "SwallowEngine"
	group ""

project "Bomberman"
	location "Bomberman"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"SwallowEngine/Swallow/vendor/spdlog/include",
		"SwallowEngine/Swallow/src",
		"SwallowEngine/%{IncludeDir.GLFW}",
		"SwallowEngine/%{IncludeDir.Glad}",
		"SwallowEngine/%{IncludeDir.glm}",
		"SwallowEngine/%{IncludeDir.ImGui}"
	}

	links
	{
		"Swallow"
	}

	filter "system:macosx"
        systemversion "latest"

        defines
        {
            "SW_PLATFORM_MACOSX"
		}
		
		links
		{
			"Cocoa.framework",
			"IOKit.framework",
			"OpenGL.framework",
			"GLUT.framework",
			"CoreVideo.framework",
			"GLFW",
			"Glad",
			"ImGui"
		}

		postbuildcommands { "echo \"cd %{prj.name} && ../bin/" .. outputdir .. "/%{prj.name}/%{prj.name}\" > ../Run.sh" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"
		optimize "on"
