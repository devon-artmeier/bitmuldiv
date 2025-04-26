cmake_minimum_required(VERSION 3.16)
project(bitshift_mul_div LANGUAGES CXX)

add_executable(bitshift_mul_div
	"src/calculate.cpp"
	"src/helpers.cpp"
	"src/main.cpp")