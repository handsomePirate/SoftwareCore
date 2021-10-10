#include "SoftwareCore/Logger.hpp"
#include <stdarg.h>
#include <stdio.h>

Core::Logger::Logger(bool verbose)
	: verbose_(verbose) {}

void Core::Logger::Log(Core::LoggerSeverity severity, const char* message, ...)
{
	if (severity == Core::LoggerSeverity::Trace && !verbose_)
	{
		return;
	}

	va_list args;
	va_start(args, message);

	char buffer[MaxMessageLength];
	char* p = buffer;

	// Do printf % magic
	const int n = _vsnprintf_s(buffer, sizeof buffer - 2, message, args);

	// Make sure the message is properly ended
	p += (n < 0) ? sizeof buffer - 2 : n;

	*p = '\n';
	*(p + 1) = '\0';

	va_end(args);

	for (auto& function : loggingFunctions_)
	{
		function.second(buffer, severity);
	}
}

Core::uuid Core::Logger::SetNewOutput(LogFunction logFunction)
{
	uuid interfaceId = uuidSystem_.Get();
	loggingFunctions_.insert(std::pair<uuid, LogFunction>(interfaceId, logFunction));
	return interfaceId;
}

void Core::Logger::RemoveOutput(uuid outputId)
{
	loggingFunctions_.erase(outputId);
}
