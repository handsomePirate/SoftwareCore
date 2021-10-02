#include "UUID.hpp"

Core::uuid Core::UUIDSystem::Get()
{
	return current_.fetch_add(1);
}