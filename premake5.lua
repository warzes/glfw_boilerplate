workspace "GLFWBoilerPlate"
    configurations { "Debug", "Release" }
    startproject "Project"

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG" }
		runtime "Debug"
		optimize "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
		runtime "Release"
		optimize "Full"
        flags { "LinkTimeOptimization" }

project "Project"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
	architecture "x86_64"
	editandcontinue "Off"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"
	
	includedirs
	{
		"libs/",
		"libs/glad/include/",
		"libs/glfw/include/",
		"libs/glm/",	
	}
    
	files
	{
		"src/**.c",
		"src/**.cpp",
		"src/**.h",
	}

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }