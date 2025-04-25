calculate();

function calculateMultiplication(multiplier)
{
	switch (multiplier) {
		case 0:
			setMultiplicationAddResult("0");
			setMultiplicationSubResult("0");
			return;
		case 1:
			setMultiplicationAddResult("n");
			setMultiplicationSubResult("n");
			return;
		case -1:
			setMultiplicationAddResult("-n");
			setMultiplicationSubResult("-n");
			return;
	}

	let negative = multiplier < 0;
	multiplier = Math.abs(multiplier);

	let steps  = [[], []];

	for (let mode = 0; mode <= 1; mode++) {
		let multiplier_work = multiplier;
		let cur_bit         = 0;

		if (mode != 0) {
			let sub_base = Math.pow(2, Math.floor((Math.log2(multiplier_work) + 1)));

			steps[mode].push(Math.log2(sub_base));
			multiplier_work = sub_base - multiplier_work;
		}
		
		while (multiplier_work != 0) {
			if ((multiplier_work % 2) == 1) {
				steps[mode].push(cur_bit);
			}

			multiplier_work = Math.floor(multiplier_work / 2);
			cur_bit++;
		}

		steps[mode].sort((a, b) => a - b);
		if (mode != 0) {
			steps[mode].reverse();
		}
	}

	for (let mode = 0; mode <= 1; mode++) {
		let result = "";

		if (negative && steps[mode].length > 0) {
			result += "-(";
		}

		for (let i = 0; i < steps[mode].length; i++) {
			if (i > 0) {
				result += (mode == 0) ? " + " : " - ";
			}

			if (steps[mode][i] == 0) {
				result += "n";
			} else {
				if (steps[mode].length > 1) {
					result += "(";
				}
				result += "n << " + steps[mode][i];
				if (steps[mode].length > 1) {
					result += ")";
				}
			}
		}

		if (negative && steps[mode].length > 0) {
			result += ")";
		}
		
		(mode == 0) ? setMultiplicationAddResult(result) : setMultiplicationSubResult(result);
	}
}

function calculateDivision(divisor, step_count)
{
	switch (divisor) {
		case 0:
			setDivisionResult("Cannot divide by 0.");
			setDivisionError(divisor, divisor);
			return;
		case 1:
			setDivisionResult("n");
			setDivisionError(divisor, divisor);
			return;
		case -1:
			setDivisionResult("-n");
			setDivisionError(divisor, divisor);
			return;
	}

	let negative = divisor < 0;
	divisor = Math.abs(divisor);

	let reciprocal      = 1 / divisor;
	let reciprocal_calc = reciprocal;
	let actual          = 0;
	let cur_bit         = 0;
	let cur_step        = 0;
	let steps           = [];

	while (reciprocal_calc != 0 && cur_step < step_count) {
		reciprocal_calc *= 2;
		cur_bit++;

		if (reciprocal_calc >= 1) {
			steps.push(cur_bit);

			reciprocal_calc -= 1;
			actual += 1 / Math.pow(2, cur_bit);
			cur_step++;
		}
	}

	let result = "";

	if (negative && steps.length > 0) {
		result += "-(";
	}

	for (let i = 0; i < steps.length; i++) {
		if (i > 0) {
			result += " + ";
		}

		if (steps[i] == 0) {
			result += "n";
		} else {
			if (steps.length > 1) {
				result += "(";
			}
			result += "n >> " + steps[i];
			if (steps.length > 1) {
				result += ")";
			}
		}
	}

	if (negative && steps.length > 0) {
		result += ")";
	}

	setDivisionResult(result);
	setDivisionError(divisor * (negative ? -1 : 1), (1.0 / actual) * (negative ? -1 : 1));
}

function calculate()
{
	let value = inputToInt("value");

	if (isNaN(value)) {
		setMultiplicationAddResult("Invalid multiplier");
		setMultiplicationSubResult("Invalid multiplier");
		setDivisionResult("Invalid divisor");
		setDivisionError(0, 0);
	} else {
		calculateMultiplication(value);

		let division_steps = inputToInt("division-steps")
		if (isNaN(division_steps) || division_steps <= 0) {
			setDivisionResult("Invalid max division step count");
			setDivisionError(0, 0);

		} else {
			calculateDivision(value, division_steps);
		}
	}
}

function setMultiplicationAddResult(result)
{
	document.getElementById("muliplication-result-add").value = result;
	resizeTextAreas();
}

function setMultiplicationSubResult(result)
{
	document.getElementById("muliplication-result-sub").value = result;
	resizeTextAreas();
}

function setDivisionResult(result)
{
	document.getElementById("division-result").value = result;
	resizeTextAreas();
}

function setDivisionError(original, actual)
{
	if (original == 0 || actual == 0) {
		document.getElementById("division-error").value = "";
	} else {
		let original_reciprocal = 1.0 / original;
		let actual_reciprocal   = 1.0 / actual;
		let error               = actual_reciprocal - original_reciprocal;

		let error_text = getDecimal(error) + " (";
		
		if (error == 0) {
			error_text += "0";
		} else {
			error_text += getFraction(1.0 / error);
		}

		document.getElementById("division-error").value = error_text + ")\n" +
		                                                  getDecimal(original_reciprocal) + " (" + getFraction(original) + ") -> " +
		                                                  getDecimal(actual_reciprocal) + " (" + getFraction(actual) + ")";
	}

	resizeTextAreas();
}

function resizeTextAreas()
{
	let box = document.getElementById("muliplication-result-add");
	box.style.height = "auto";
	box.style.height = box.scrollHeight + "px";

	box = document.getElementById("muliplication-result-sub");
	box.style.height = "auto";
	box.style.height = box.scrollHeight + "px";


	box = document.getElementById("division-result");
	box.style.height = "auto";
	box.style.height = box.scrollHeight + "px";
	
	box = document.getElementById("division-error");
	box.style.height = "auto";
	box.style.height = box.scrollHeight + "px";
}

function inputToInt(id)
{
	let value_text = document.getElementById(id).value;
	let value = Number(value_text);
	
	if (value_text.length == 0 || Math.abs(value - Math.floor(value)) > 0) {
		value = NaN;
	}
	return value;
}

function getDecimal(value)
{
	let precision = 15;

	let negative = value < 0;
	value = Math.abs(value);

	let integer = Math.floor(value);
	let decimal = Math.floor((value - integer) * Math.pow(10, precision));

	let str = integer;

	if (decimal != 0) {
		str += "." + new Array(precision - Math.floor(Math.log10(decimal))).join('0') + decimal.toString().replace(/0+$/, "");
	}

	return (negative ? "-" : "") + str;
}

function getFraction(value)
{
	switch (value) {
		case 0:
			return "0";
		case 1:
			return "1";
		case -1:
			return "-1";
	}
	return (value < 0 ? "-" : "") + "1/" + getDecimal(Math.abs(value));
}