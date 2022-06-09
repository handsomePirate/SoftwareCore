#include "SoftwareCore/String.hpp"
#include <sstream>

std::vector<std::string> Core::String::Split(const std::string& str, const std::string& delimiters,
	const bool trimEmptyStrings)
{
	std::stringstream ss;
	std::vector<std::string> result;
	int lastString = -1;
	for (const char& c : str)
	{
		bool delimiter = false;
		for (const char& d : delimiters)
		{
			if (d == c)
			{
				delimiter = true;
				break;
			}
		}
		if (delimiter)
		{
			if (!ss.str().empty() || !trimEmptyStrings)
			{
				result.push_back(ss.str());
				ss.str(std::string());
			}
		}
		else
		{
			ss << c;
		}
	}

	if (!ss.str().empty() || !trimEmptyStrings)
	{
		result.push_back(ss.str());
	}

	return result;
}

std::string Core::String::NumberToHexString(uint64_t n)
{
	std::stringstream ss;
	ss << std::hex << n;
	return ss.str();
}

// xxxx-xx-xxxxxx-xxxx
std::string Core::String::NumberToUUIDString(uint64_t n)
{
	std::string hexString = NumberToHexString(n);

	std::stringstream ss;
	ss << hexString.substr(0, 4) << '-' << hexString.substr(4, 2) << '-'
		<< hexString.substr(6, 6) << '-' << hexString.substr(12, 4);

	return ss.str();
}

uint64_t Core::String::HexStringToNumber(const std::string& str)
{
	std::stringstream ss(str);
	uint64_t n;
	ss >> std::hex >> n;
	return n;
}

uint64_t Core::String::UUIDStringToNumber(const std::string& str)
{
	// TODO: Check if it is a valid UUID
	std::vector<std::string> strParts = Split(str, "-");
	std::stringstream ss;
	for (const std::string& strPart : strParts)
	{
		ss << strPart;
	}
	return HexStringToNumber(ss.str());
}
