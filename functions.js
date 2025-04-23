changeMode(document.getElementById("division-mode"));

function calculateMultiplication(multiplier)
{
	switch (multiplier) {
		case 0:
			setResult("0");
			return;

		case 1:
			setResult("n");
			return;
			
		case -1:
			setResult("-n");
			return;
	}

	let result = "";

	let negative = multiplier < 0;
	if (negative) {
		multiplier = -multiplier;
		result += "-(";
	}

	let bit_pos = 0;
	let printed = false;

	while (multiplier != 0) {
		if ((multiplier % 2) == 1) {
			if (printed) {
				result += " + ";
			}

			if (bit_pos == 0) {
				result += "n";
			} else {
				result += "(n << " + bit_pos + ")";
			}

			printed = true;
		}

		multiplier = Math.floor(multiplier / 2);
		bit_pos++;
	}

	if (negative) {
		result += ")";
	}

	setResult(result);
}

function calculateDivision(divisor, steps)
{
	switch (divisor) {
		case 0:
			setResult("Cannot divide by 0.");
			setDivisionError(0, 0);
			return;

		case 1:
			setResult("n");
			setDivisionError(0, 0);
			return;
			
		case -1:
			setResult("-n");
			setDivisionError(0, 0);
			return;
	}

	let result = "";

	let negative = divisor < 0;
	if (negative) {
		divisor = -divisor;
		result += "-(";
	}

	let reciprocal      = 1 / divisor;
	let reciprocal_calc = reciprocal;
	let actual          = 0;
	let bit_pos         = 0;
	let cur_step        = 0;
	let printed         = false;

	while (reciprocal_calc != 0 && cur_step < steps) {
		reciprocal_calc *= 2;
		bit_pos++;

		if (reciprocal_calc >= 1) {
			reciprocal_calc -= 1;
			actual += 1 / (1 << bit_pos);
			cur_step++;

			if (printed) {
				result += " + ";
			}

			result += "(n >> " + bit_pos + ")";
			printed = true;
		}
	}

	if (negative) {
		result += ")";
	}

	setResult(result);
	setDivisionError(reciprocal, actual);
}

function calculate()
{
	let value = inputToInt("value");
	let division_mode = document.getElementById("division-mode").checked;

	if (isNaN(value)) {
		setResult("Invalid " + (division_mode ? "divisor" : "multiplier"));
	} else {
		if (!division_mode) {
			calculateMultiplication(value);
		} else {
			let steps = inputToInt("division-steps")
			if (isNaN(steps) || steps <= 0) {
				setResult("Invalid max division step count");
			} else {
				calculateDivision(value, steps);
			}
		}
	}
}

function setResult(result)
{
	document.getElementById("result").innerText = result;
	resizeTextAreas();
}

function setDivisionError(reciprocal, actual)
{
	document.getElementById("division-error").innerText = Math.abs(actual - reciprocal) + " (" + reciprocal + " -> " + actual + ")";
	resizeTextAreas();
}

function resizeTextAreas()
{
	let box = document.getElementById("result");
	box.style.height = "auto";
	box.style.height = box.scrollHeight + "px";
	
	box = document.getElementById("division-error");
	box.style.height = "auto";
	box.style.height = box.scrollHeight + "px";
}

function changeMode(checkbox)
{
	if (checkbox.checked) {
		document.getElementById("value-header").innerText = "Divisor"
		document.getElementById("division-step-block").style = "";
		document.getElementById("division-error-block").style = "";
	} else {
		document.getElementById("value-header").innerText = "Multiplier"
		document.getElementById("division-step-block").style.display = "none";
		document.getElementById("division-error-block").style.display = "none";
	}

	calculate();
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