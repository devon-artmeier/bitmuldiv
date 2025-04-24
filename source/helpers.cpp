/*
	Copyright(c) 2025 Devon Artmeier

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

long long GetGcd(const long long a, const long long b)
{
	if (a == 0) {
		return b;
	} else if (b == 0) {
		return a;
	}

	if (a < b) {
		return GetGcd(a, b % a);
	}
	return GetGcd(b, a % b);
}

std::string GetFraction(double value)
{
	std::stringstream fraction;

	bool negative = value < 0;
	value = std::abs(value);

	long long integral             = static_cast<long long>(value);
	double    decimal              = value - integral;
	long long precision            = 10000000000000;
	double    reciprocal           = 1.0 / value;
	double    reciprocal_decimal   = reciprocal - static_cast<long long>(reciprocal);
	double    reciprocal_precision = 0.00000000000015;

	if (integral != 0) {
		if (negative) {
			fraction << "-";
		}

		fraction << integral;
		if (decimal != 0) {
			fraction << negative ? " - " : " + ";
		}
	}

	long long gcd         = GetGcd(static_cast<long long>(decimal * precision), precision);
	long long numerator   = static_cast<long long>(decimal * precision) / gcd;
	long long denominator = precision / gcd;

	if (reciprocal_decimal <= reciprocal_precision || reciprocal_decimal >= (1 - reciprocal_precision)) {
		numerator   = 1;
		denominator = std::round(reciprocal);
	}

	if (decimal != 0) {
		if (negative) {
			fraction << "-";
		}
		fraction << std::to_string(numerator) + "/" + std::to_string(denominator);
	} else if (integral == 0) {
		fraction << "0";
	}

	return fraction.str();
}