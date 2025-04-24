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
					throw std::runtime_error(("Invalid max division step count \"" + (std::string)argv[i] + "\".").c_str());
				}

				if (division_steps <= 0) {
					throw std::runtime_error(("Invalid max division step count \"" + (std::string)argv[i] + "\".").c_str());
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