#pragma once
#include <string>

namespace Core
{
	class Filesystem
	{
	public:
		Filesystem(const std::string& executablePath);
		~Filesystem();

		bool IsPathRelative(const std::string& path) const;
		std::string ExecutableName() const;
		std::string GetAbsolutePath(const std::string& relativePath) const;
		bool FileExists(const std::string& path) const;
		size_t GetFileSize(const std::string& path) const;
		void ReadFile(const std::string& path, void* data, size_t size) const;
		std::string Filename(const std::string& path) const;
		std::string Extension(const std::string& path) const;
		std::string RemoveExtension(const std::string& path) const;

	private:
		struct Private;
		Private* p_;
	};
}
