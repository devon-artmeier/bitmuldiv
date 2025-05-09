cmake_minimum_required(VERSION 3.16)
project(bitmuldiv LANGUAGES CXX)

add_executable(bitmuldiv
	"src/calculate.cpp"
	"src/helpers.cpp"
	"src/main.cpp")

install(TARGETS bitmuldiv)