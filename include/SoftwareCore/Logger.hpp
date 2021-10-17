#pragma once
#include "UUID.hpp"
#include <unordered_map>

#define LOGGER_DO_TRACE
#undef LOGGER_DO_TRACE

namespace Core
{
	enum class LoggerSeverity
	{
		Fatal,
		Error,
		Warn,
		Info,
		Debug,
		Trace
	};

	const int MaxMessageLength = 1024;

	typedef void(*LogFunction)(const char*, LoggerSeverity);

	class Logger
	{
	public:
		Logger(bool verbose = false);
		~Logger() = default;

		void Log(LoggerSeverity severity, const char* message, ...);

		uuid SetNewOutput(LogFunction loggerInterface);
		void RemoveOutput(uuid outputId);

	private:
		bool verbose_;
		UUIDSystem uuidSystem_;
		std::unordered_map<uuid, LogFunction> loggingFunctions_;
	};
}

#if defined(DEBUG)
#define CoreLogTrace(logger, format, ...) (logger.Log)(::Core::LoggerSeverity::Trace, format, ##__VA_ARGS__)
#define CoreLogDebug(logger, format, ...) (logger.Log)(::Core::LoggerSeverity::Debug, format, ##__VA_ARGS__)
#else
#define CoreLogTrace(logger, format, ...)
#define CoreLogDebug(logger, format, ...)
#endif

#define CoreLogInfo(logger, format, ...) (logger.Log)(::Core::LoggerSeverity::Info, format, ##__VA_ARGS__)
#define CoreLogWarn(logger, format, ...) (logger.Log)(::Core::LoggerSeverity::Warn, format, ##__VA_ARGS__)
#define CoreLogError(logger, format, ...) (logger.Log)(::Core::LoggerSeverity::Error, format, ##__VA_ARGS__)
#define CoreLogFatal(logger, format, ...) (logger.Log)(::Core::LoggerSeverity::Fatal, format, ##__VA_ARGS__)
