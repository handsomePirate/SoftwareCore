#pragma once
#include <string>
#include <vector>

namespace Core
{
	namespace String
	{
		std::vector<std::string> Split(const std::string& str, const std::string& delimiters,
			const bool trimEmptyStrings = false);

		std::string NumberToHexString(uint64_t n);
		std::string NumberToUUIDString(uint64_t n);

		uint64_t HexStringToNumber(const std::string& str);
		uint64_t UUIDStringToNumber(const std::string& str);
	}
}
