#define _CRT_SECURE_NO_DEPRECATE
#include "SoftwareCore/Filesystem.hpp"

struct Core::Filesystem::Private
{
    std::filesystem::path Root;
    std::filesystem::path ExecutableName;
};

Core::Filesystem::Filesystem(const std::string& executablePath)
    : p_(new Filesystem::Private)
{
    p_->Root = std::filesystem::path(executablePath);
    p_->ExecutableName = p_->Root.filename();
    p_->Root.remove_filename();
}

Core::Filesystem::Filesystem(const std::filesystem::path& executablePath)
    : p_(new Filesystem::Private)
{
    p_->Root = executablePath;
    p_->ExecutableName = p_->Root.filename();
    p_->Root.remove_filename();
}

Core::Filesystem::~Filesystem()
{
    delete p_;
}

bool Core::Filesystem::IsPathRelative(const std::string& path) const
{
    return std::filesystem::path(path).is_relative();
}

std::string Core::Filesystem::ExecutableName() const
{
    return p_->ExecutableName.replace_extension().string();
}

std::string Core::Filesystem::GetAbsolutePath(const std::string& relativePath) const
{
    std::filesystem::path relative(relativePath);
    std::filesystem::path absolute = p_->Root;
    absolute += relative;
    return absolute.lexically_normal().make_preferred().string();
}

bool Core::Filesystem::FileExists(const std::string& path) const
{
    std::filesystem::path fsPath(path);
    std::filesystem::path absolutePath = fsPath.is_relative() ? std::filesystem::path(GetAbsolutePath(path)) : fsPath;
    return std::filesystem::exists(absolutePath);
}

size_t Core::Filesystem::GetFileSize(const std::string& path) const
{
    FILE* f;
    f = fopen(path.c_str(), "rb");

    if (!f)
    {
        return 0;
    }

    fseek(f, 0, SEEK_END);
    const size_t fileSize = ftell(f);
    fclose(f);
    return fileSize;
}

void Core::Filesystem::ReadFile(const std::string& path, void* data, size_t size) const
{
    FILE* f;
    fopen_s(&f, path.c_str(), "rb");

    if (!f)
    {
        *(char*)data = '\0';
        return;
    }

    fread(data, size, 1, f);
    fclose(f);
}

std::string Core::Filesystem::Filename(const std::string& path) const
{
    std::filesystem::path fsPath(path);
    return fsPath.filename().string();
}

std::string Core::Filesystem::Extension(const std::string& path) const
{
    std::filesystem::path fsPath(path);
    return fsPath.extension().string();
}

std::string Core::Filesystem::RemoveExtension(const std::string& path) const
{
    std::filesystem::path fsPath(path);
    fsPath.replace_extension();
    return fsPath.string();
}
