SoftwareCoreInclude = path.getabsolute("../../include", os.getcwd())

project "SoftwareCore"
	kind "StaticLib"
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	location ""
	targetdir "../../build/%{cfg.buildcfg}"
	objdir "obj/%{cfg.buildcfg}"
	files { "../../src/**.hpp", "../../src/**.cpp", "../../include/**.hpp" }
	
	includedirs {
		SoftwareCoreInclude
	}
	
	filter "system:windows"
		systemversion "latest"
	filter{}
	
	filter "configurations:Debug"
		defines { "SC_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "SC_RELEASE" }
		runtime "Release"
		optimize "On"

	filter {}