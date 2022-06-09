#pragma once
#include "BigIntegers.hpp"
#include <stdint.h>
#include <atomic>
#include <string>

namespace Core
{
	typedef uint64_t uuid;

	class UUIDSystem
	{
	public:
		UUIDSystem();
		~UUIDSystem() = default;

		void SetSeed(uint64_t seed);
		uuid Get();
	private:
		uint128_t current_;
	};
}
