#include "UUID.hpp"

uuid UUIDSystem::Get()
{
	return current_.fetch_add(1);
}