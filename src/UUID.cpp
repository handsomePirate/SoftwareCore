#include "SoftwareCore/UUID.hpp"
#include <time.h>

Core::UUIDSystem::UUIDSystem()
{
	srand((unsigned int)time(0));
	SetSeed(rand());
	Get();
}

void Core::UUIDSystem::SetSeed(uint64_t seed)
{
	current_ = seed;
}

Core::uuid Core::UUIDSystem::Get()
{
	current_ *= 0xda942042e4dd58b5;
	return current_ >> 64;
}