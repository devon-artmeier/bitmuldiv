/*
	Copyright (c) 2025 Devon Artmeier

	Permission to use, copy, modify, and /or distribute this software
	for any purpose with or without fee is hereby granted.

	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
	WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIE
	WARRANTIES OF MERCHANTABILITY AND FITNESS.IN NO EVENT SHALL THE
	AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
	DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
	PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
	TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
	PERFORMANCE OF THIS SOFTWARE.
*/

#include "shared.hpp"

std::string StringToLower(const std::string& str)
{
	std::string lower_str = str;
	std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), [](unsigned char c) { return std::tolower(c); });
	return lower_str;
}

bool CheckArgument(const int argc, char* argv[], int& index, const std::string& option, const bool ignore_case)
{
	std::string option_copy = option;
	if (ignore_case) {
		option_copy = StringToLower(option);
	}

	if (strcmp(argv[index], ("-" + option_copy).c_str()) == 0) {
		if (++index >= argc) {
			throw std::runtime_error(("Missing parameter for \"-" + option + "\"").c_str());
		}
		return true;
	}
	return false;
}

std::string GetDecimal(double value)
{
	const int precision = 15;

	bool negative = value < 0;
	value = std::abs(value);

	long long integer = std::floor(value);
	long long decimal = (value - std::floor(value)) * std::pow(10, precision);

	std::string str = std::to_string(integer);

	if (decimal != 0) {
		str += "." + std::string(precision - static_cast<int>(std::log10(decimal) + 1), '0') + std::to_string(decimal);
		str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	}

	return (negative ? "-" : "") + str;
}

std::string GetFraction(double value)
{
	if (value == 0) {
		return "0";
	} else if (value == 1) {
		return "1";
	} else if (value == -1) {
		return "-1";
	}
	return (std::string)(value < 0 ? "-" : "") + "1/" + GetDecimal(std::abs(value));
}