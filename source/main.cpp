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

static void CalculateMultiplication(int multiplier)
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
	if (negative) {
		multiplier = -multiplier;
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

static void CalculateDivision(int divisor, int steps)
{
	if (divisor == 0) {
		throw std::runtime_error("Cannot divide by 0.");
	}

	std::cout << "result = ";

	switch (divisor) {
		case 1:
			std::cout << "n" << std::endl;
			return;

		case -1:
			std::cout << "-n" << std::endl;
			return;
	}

	bool negative = divisor < 0;
	if (negative) {
		divisor = -divisor;
		std::cout << "-(";
	}

	float reciprocal      = 1.0f / divisor;
	float reciprocal_calc = reciprocal;
	float actual          = 0.0f;
	int   bit_pos         = 0;
	int   cur_step        = 0;
	bool  printed         = false;

	while (reciprocal_calc != 0 && cur_step < steps) {
		reciprocal_calc *= 2.0f;
		bit_pos++;
		
		if (reciprocal_calc >= 1.0f) {
			reciprocal_calc -= 1.0f;
			actual += 1.0f / (1 << bit_pos);
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
	std::cout << std::endl << 
	             "Margin of error: " << std::abs(actual - reciprocal) << " " << "(" << reciprocal << " -> " << actual << ")" << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Usage: bitshift_mul_div <-d> <-s [steps]> [value]" << std::endl << std::endl <<
		             "           <-d>         - Set to division mode" << std::endl <<
		             "           <-s [steps]> - Max division step count (default = 3)" << std::endl <<
		             "           [value]      - Multiplier or divisor (integers only)" << std::endl << std::endl;
		return -1;
	}

	try {
		bool division_mode      = false;
		int  value              = 0;
		bool got_value          = false;
		int  division_steps     = 3;
		bool got_division_steps = false;

		for (int i = 1; i < argc; i++) {
			if (StringToLower(argv[i]).compare("-d") == 0) {
				division_mode = true;
				continue;
			}

			if (CheckArgument(argc, argv, i, "s")) {
				if (got_division_steps) {
					throw std::runtime_error("Max division step count already defined.");
				}

				try {
					division_steps = std::stoi(argv[i], nullptr, 10);
					got_division_steps = true;
				} catch (...) {
					throw std::runtime_error(("Invalid Max division step count \"" + (std::string)argv[i] + "\".").c_str());
				}

				if (division_steps == 0) {
					throw std::runtime_error("Max division step count cannot be 0.");
				}
				continue;
			}

			if (got_value) {
				throw std::runtime_error("Multiplier/divisor already defined.");
			}

			try {
				value = std::stoi(argv[i], nullptr, 10);
				got_value = true;
			} catch (...) {
				throw std::runtime_error(("Invalid multiplier/divisor \"" + (std::string)argv[i] + "\".").c_str());
			}
		}
		
		if (!got_value) {
			throw std::runtime_error("Multiplier/divisor not defined.");
		}

		if (!division_mode) {
			CalculateMultiplication(value);
		} else {
			CalculateDivision(value, division_steps);
		}
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		return -1;
	}
}