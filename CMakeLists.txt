cmake_minimum_required(VERSION 3.8)
project(Project_8_Interpreter_A)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Input.cpp
        Main.cpp
        Parse.h
        String.h
        test1.blip
        test2.blip
        test3.blip
        test4.blip All.h run.cpp All1.h)

add_executable(Project_8_Interpreter_A ${SOURCE_FILES})