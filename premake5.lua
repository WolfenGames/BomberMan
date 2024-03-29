workspace "Bomberman"

startproject "Bomberman"

architecture "x64"

enginedir = "SwallowEngine/Swallow/"

include "SwallowEngine/Swallow"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/PowerUps/**.cpp",
		"%{prj.name}/src/PowerUps/**.hpp"
	}

	includedirs
	{
		enginedir .. "vendor/spdlog/include",
		enginedir .. "src",
		enginedir .. "src/PowerUps",
		enginedir .. "%{IncludeDir.GLFW}",
		enginedir .. "%{IncludeDir.Glad}",
		enginedir .. "%{IncludeDir.glm}",
		enginedir .. "%{IncludeDir.freetype}",
		enginedir .. "%{IncludeDir.ImGui}",
		enginedir .. "vendor/imgui/misc",
		enginedir .. "%{IncludeDir.AssImp}",
		enginedir .. "%{IncludeDir.AssImpBuild}",
		enginedir .. "%{IncludeDir.OpenAL}"
	}

	links
	{
		"Swallow"
	}

	filter "system:macosx"
        systemversion "latest"

	buildoptions { "-Wall", "-Wextra", "-Werror"}

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
			"OpenAL.framework",
			"AudioUnit.framework",
			"AudioToolbox.framework",
			"CoreAudio.framework",
			"GLFW",
			"Glad",
			"ImGui",
			"OpenAL",
			"freetype",
			"AssImp"
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
