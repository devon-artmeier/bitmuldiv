# Multiplication/Division Bitshift Calculator

[![Build Status](https://github.com/devon-artmeier/bitshift_mul_div/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/devon-artmeier/bitshift_mul_div/actions/workflows/cmake-multi-platform.yml)

This is a tool to calculate multiplications and divisions using only bitshifts.

## Usage
    
    Usage: bitshift_mul_div <-d> <-s [steps]> [value]
               <-d>         - Set to division mode
               <-s [steps]> - Max division step count (default = 3)
               [value]      - Multiplier or divisor (integers only)

## What About Fractions?

Because this tool only deals with integers, if you want to include fractional multiplications and divisions, you should split them into separate calculations.

For example, if you want to multiply by 1.5, then you should do a multiplication by 3 and then a division by 2. This is because **(n * 1.5) = (n * (3/2))**.

If you want to divide by 1.5, then you do a multiplication by 2 and then a division by 3. This is because a division is the same as a multiplication of the reciprocal of the value you want to divide by (in this case **(n / (3/2)) = (n * (2/3))**).

## What About Modulo?

That can simply be done by taking the quotient of a division, multiplying back the divisor, and getting the difference between that and the dividend, like so:

    quotient = dividend / divisor
    modulo   = dividend - (quotient * divisor)
