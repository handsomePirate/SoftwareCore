workspace "SoftwareCore"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Test"
	location ""
	
	flags
	{
		"MultiProcessorCompile"
	}
	
include "../dependencies.lua"

include "../proj/SoftwareCore"
include "../proj/Test"