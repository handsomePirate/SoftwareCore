#define SC_DEBUG
#include <SoftwareCore/UUID.hpp>
#include <SoftwareCore/Logger.hpp>
#include <SoftwareCore/DefaultLogger.hpp>
#include <SoftwareCore/Filesystem.hpp>
#include <SoftwareCore/Process.hpp>v
#include <SoftwareCore/String.hpp>
#include <iostream>

void OutputMessageConsole(const char* message, Core::LoggerSeverity severity)
{
	const char* traceSev = "[Trace] ";
	const char* debugSev = "[Debug] ";
	const char* infoSev = "[Info] ";
	const char* warnSev = "[Warn] ";
	const char* errorSev = "[Error] ";
	const char* fatalSev = "[Fatal] ";

	switch (severity)
	{
	case Core::LoggerSeverity::Trace:
		std::cout << traceSev;
		break;
	case Core::LoggerSeverity::Debug:
		std::cout << debugSev;
		break;
	case Core::LoggerSeverity::Info:
		std::cout << infoSev;
		break;
	case Core::LoggerSeverity::Warn:
		std::cout << warnSev;
		break;
	case Core::LoggerSeverity::Error:
		std::cout << errorSev;
		break;
	case Core::LoggerSeverity::Fatal:
		std::cout << fatalSev;
		break;
	}

	std::cout << message;
}

int main(int argc, char* argv[])
{
	Core::Filesystem filesystem(CoreProcess.GetRuntimePath());
	std::string pathToMain = filesystem.GetAbsolutePath("../../src/Main.cpp");

	Core::uuid firstOutputId = DefaultLogger.SetNewOutput(OutputMessageConsole);

	CoreLogDebug(DefaultLogger, "first id %llu", firstOutputId);

	Core::uuid secondOutputId = DefaultLogger.SetNewOutput(OutputMessageConsole);

	std::string uuidStr = Core::String::NumberToUUIDString(secondOutputId);
	uint64_t backToNumber = Core::String::UUIDStringToNumber(uuidStr);

	CoreLogInfo(DefaultLogger, "testing %s", filesystem.FileExists(pathToMain) ? "true" : "false");

	DefaultLogger.RemoveOutput(secondOutputId);

	CoreLogFatal(DefaultLogger, "testing %i", 2);

	return 0;
}