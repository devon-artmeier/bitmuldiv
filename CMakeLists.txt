cmake_minimum_required(VERSION 3.16)
project(bitshift_mul_div LANGUAGES CXX)

add_executable(bitshift_mul_div
	"source/calculate.cpp"
	"source/helpers.cpp"
	"source/main.cpp")