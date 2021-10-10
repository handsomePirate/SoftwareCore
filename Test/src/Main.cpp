#define SC_DEBUG
#include <SoftwareCore/Logger.hpp>
#include <SoftwareCore/Filesystem.hpp>
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
	Core::Logger logger;
	Core::Filesystem filesystem(argv[0]);
	std::string pathToMain = filesystem.GetAbsolutePath("../../src/Main.cpp");

	Core::uuid firstOutputId = logger.SetNewOutput(OutputMessageConsole);

	CoreLogDebug(logger, "testing %s", pathToMain.c_str());

	Core::uuid secondOutputId = logger.SetNewOutput(OutputMessageConsole);

	CoreLogInfo(logger, "testing %s", filesystem.FileExists(pathToMain) ? "true" : "false");

	logger.RemoveOutput(secondOutputId);

	CoreLogFatal(logger, "testing %i", 2);

	return 0;
}