#pragma once
#include <SoftwareCore/Singleton.hpp>
#include <filesystem>

namespace Core
{
	class Process
	{
	public:
		Process();

		std::filesystem::path GetRuntimePath() const;

	private:
		std::filesystem::path runtimePath;
	};
}

#define CoreProcess ::Core::Singleton<::Core::Process>::GetInstance()
