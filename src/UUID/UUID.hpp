#pragma once
#include <stdint.h>
#include <atomic>

typedef uint64_t uuid;

class UUIDSystem
{
public:
	UUIDSystem() = default;
	~UUIDSystem() = default;

	uuid Get();
private:
	std::atomic<uint64_t> current_ = 0;
};