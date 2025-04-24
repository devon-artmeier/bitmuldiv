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

static void PrintMarginOfError(const double original, const double actual)
{
	double original_reciprocal = 1.0 / original;
	double actual_reciprocal   = 1.0 / actual;
	double error               = actual_reciprocal - original_reciprocal;

	std::cout << std::endl <<
		"Margin of error: " << error << " (";
	
	if (error == 0) {
		std::cout << "0";
	} else {
		std::cout << GetFraction(1.0 / error);
	}

	std::cout << ")" << std::endl << "                 " <<
	             original_reciprocal << " (" << GetFraction(original) << ") -> " <<
	             actual_reciprocal << " (" << GetFraction(actual) << ")" << std::endl;
}

void CalculateMultiplication(int multiplier)
{
	std::cout << "result = ";

	switch (multiplier) {
		case 0:
			std::cout << "0" << std::endl;
			return;

		case 1:
			std::cout << "n" << std::endl;
			return;

		case -1:
			std::cout << "-n" << std::endl;
			return;
	}

	bool negative = multiplier < 0;
	multiplier = std::abs(multiplier);

	if (negative) {
		std::cout << "-(";
	}

	int  bit_pos = 0;
	bool printed = false;

	while (multiplier != 0) {
		if ((multiplier & 1) == 1) {
			if (printed) {
				std::cout << " + ";
			}

			if (bit_pos == 0) {
				std::cout << "n";
			} else {
				std::cout << "(n << " << bit_pos << ")";
			}

			printed = true;
		}

		multiplier /= 2;
		bit_pos++;
	}

	if (negative) {
		std::cout << ")";
	}
	std::cout << std::endl;
}

void CalculateDivision(int divisor, const int steps)
{
	if (divisor == 0) {
		throw std::runtime_error("Cannot divide by 0.");
	}

	std::cout << "result = ";

	switch (divisor) {
		case 1:
			std::cout << "n";
			PrintMarginOfError(divisor, divisor);
			return;

		case -1:
			std::cout << "-n";
			PrintMarginOfError(divisor, divisor);
			return;
	}

	bool negative = divisor < 0;
	divisor = std::abs(divisor);

	if (negative) {
		std::cout << "-(";
	}

	double reciprocal      = 1.0 / divisor;
	double reciprocal_calc = reciprocal;
	double actual          = 0.0;
	int    bit_pos         = 0;
	int    cur_step        = 0;
	bool   printed         = false;

	while (reciprocal_calc != 0 && cur_step < steps && bit_pos < 31) {
		reciprocal_calc *= 2.0;
		bit_pos++;
		
		if (reciprocal_calc >= 1.0) {
			reciprocal_calc -= 1.0;
			actual += 1.0 / static_cast<double>(1 << bit_pos);
			cur_step++;

			if (printed) {
				std::cout << " + ";
			}

			std::cout << "(n >> " << bit_pos << ")";
			printed = true;
		}
	}

	if (negative) {
		std::cout << ")";
	}

	PrintMarginOfError(divisor * (negative ? -1 : 1), (1.0 / actual) * (negative ? -1 : 1));
}