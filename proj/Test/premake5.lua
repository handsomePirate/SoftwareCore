project "Test"
	kind "ConsoleApp"
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	location ""
	targetdir "../../Test/build/%{cfg.buildcfg}"
	objdir "obj/%{cfg.buildcfg}"
	files { "../../Test/src/**.hpp", "../../Test/src/**.cpp" }
	
	includedirs {
		"../../src",
		"../../Test/src"
	}
	
	links {
		"SoftwareCore"
	}
	
	filter "system:windows"
		systemversion "latest"
	filter{}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter {}
