SoftwareCoreInclude = path.getabsolute("../../include", os.getcwd())

project "SoftwareCore"
	kind "StaticLib"
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	location ""
	targetdir "../../build/%{cfg.buildcfg}"
	objdir "obj/%{cfg.buildcfg}"
	files {
		"../../ext/uint128_t/uint128_t.h",
		"../../ext/uint128_t/uint128_t.cpp",
		"../../ext/uint128_t/uint128_t.include",
		"../../ext/uint128_t/uint128_t.build",
		"../../ext/uint128_t/uint128_t_config.include",
		"../../ext/uint128_t/endianness.h",
		"../../src/**.hpp",
		"../../src/**.cpp",
		"../../include/**.hpp"
	}
	
	includedirs {
		SoftwareCoreInclude
	}
	
	links {
	}
	
	defines {
		"UINT128_T_BUILD"
	}
	
	filter "system:windows"
		systemversion "latest"
	filter{}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "On"

	filter {}