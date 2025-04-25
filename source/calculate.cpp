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

void CalculateMultiplication(long long multiplier)
{
	std::cout << "Multiplication:" << std::endl << "    ";

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

	std::vector<int> steps[2];

	for (int mode = 0; mode <= 1; mode++) {
		long long multiplier_work = multiplier;
		int       cur_bit         = 0;

		if (mode != 0) {
			long long sub_base = std::pow(2, std::floor(std::log2(multiplier_work) + 1));

			steps[mode].push_back(std::log2(multiplier_work));
			multiplier_work = sub_base - multiplier_work;
		}

		while (multiplier_work != 0) {
			if ((multiplier_work & 1) == 1) {
				steps[mode].push_back(cur_bit);
			}

			multiplier_work /= 2;
			cur_bit++;
		}

		std::sort(steps[mode].begin(), steps[mode].end());
		if (mode != 0) {
			std::reverse(steps[mode].begin(), steps[mode].end());
		}
	}

	int mode = (steps[0].size() <= steps[1].size()) ? 0 : 1;
	if (steps[mode].size() == 0) {
		mode ^= 1;
	}

	if (negative && steps[mode].size() > 0) {
		std::cout << "-(";
	}

	for (int i = 0; i < steps[mode].size(); i++) {
		if (i > 0) {
			std::cout << ((mode == 0) ? " + " : " - ");
		}

		if (steps[mode][i] == 0) {
			std::cout << "n";
		} else {
			if (steps[mode].size() > 1) {
				std::cout << "(";
			}
			std::cout << "n << " << steps[mode][i];
			if (steps[mode].size() > 1) {
				std::cout << ")";
			}
		}
	}

	if (negative && steps[mode].size() > 0) {
		std::cout << ")";
	}
	std::cout << std::endl;
}

static void PrintDivisionError(const double original, const double actual)
{
	double original_reciprocal = 1.0 / original;
	double actual_reciprocal   = 1.0 / actual;
	double error               = actual_reciprocal - original_reciprocal;

	std::cout << "Division margin of error: " << std::endl << "    " << GetDecimal(error) << " (";
	
	if (error == 0) {
		std::cout << "0";
	} else {
		std::cout << GetFraction(1.0 / error);
	}

	std::cout << ")" << std::endl << "    " <<
	             GetDecimal(original_reciprocal) << " (" << GetFraction(original) << ") -> " <<
	             GetDecimal(actual_reciprocal) << " (" << GetFraction(actual) << ")" << std::endl;
}

void CalculateDivision(long long divisor, const int step_count)
{
	if (divisor == 0) {
		throw std::runtime_error("Cannot divide by 0.");
	}

	std::cout << "Division:" << std::endl << "    ";

	switch (divisor) {
		case 1:
			std::cout << "n";
			PrintDivisionError(divisor, divisor);
			return;
		case -1:
			std::cout << "-n";
			PrintDivisionError(divisor, divisor);
			return;
	}

	bool negative = divisor < 0;
	divisor = std::abs(divisor);

	double           reciprocal      = 1.0 / divisor;
	double           reciprocal_calc = reciprocal;
	double           actual          = 0.0;
	int              cur_bit         = 0;
	int              cur_step        = 0;
	std::vector<int> steps;

	while (reciprocal_calc != 0 && cur_step < step_count) {
		reciprocal_calc *= 2.0;
		cur_bit++;
		
		if (reciprocal_calc >= 1.0) {
			steps.push_back(cur_bit);

			reciprocal_calc -= 1.0;
			actual += 1.0 / std::pow(2, cur_bit);
			cur_step++;
		}
	}

	if (negative && steps.size() > 0) {
		std::cout << "-(";
	}

	for (int i = 0; i < steps.size(); i++) {
		if (i > 0) {
			std::cout << " + ";
		}

		if (steps[i] == 0) {
			std::cout << "n";
		} else {
			if (steps.size() > 1) {
				std::cout << "(";
			}
			std::cout << "n >> " << steps[i];
			if (steps.size() > 1) {
				std::cout << ")";
			}
		}
	}

	if (negative && steps.size() > 0) {
		std::cout << ")";
	}
	std::cout << std::endl;

	PrintDivisionError(divisor * (negative ? -1 : 1), (1.0 / actual) * (negative ? -1 : 1));
}