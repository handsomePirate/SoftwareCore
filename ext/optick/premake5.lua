OptickInclude = os.getcwd()

project "Optick"
	kind "StaticLib"
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	location ""
	targetdir "build/%{cfg.buildcfg}"
	objdir "obj/%{cfg.buildcfg}"
	files { "optick/**.h", "optick/**.cpp" }

	flags {
		"MultiProcessorCompile"
	}

	includedirs {
		"$(VULKAN_SDK)/include"
	}

	links {
		"$(VULKAN_SDK)/lib/vulkan-1.lib",
	}

	filter "system:windows"
		systemversion "latest"
	filter{}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"

	filter {}
