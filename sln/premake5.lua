workspace "SoftwareCore"
	architecture "x64"
	configurations { "Debug", "Release" }
	location ""
	
	flags
	{
		"MultiProcessorCompile"
	}
	
include "../proj/SoftwareCore"
include "../proj/Test"