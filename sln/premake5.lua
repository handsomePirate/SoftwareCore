workspace "SoftwareCore"
	architecture "x64"
	configurations { "Debug", "Release" }
	location ""
	
	flags
	{
		"MultiProcessorCompile"
	}
	
include "../dependencies.lua"
	
include "../proj/SoftwareCore"
include "../proj/Test"