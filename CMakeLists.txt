cmake_minimum_required(VERSION 3.22)
project(Kalkulator_ONP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Kalkulator_ONP main.cpp
        CharStack.cpp
        IntStack.cpp
        ONPString.cpp
)
