cmake_minimum_required(VERSION 3.5)

project(vocabulary_trainer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(vocabulary_trainer src/main.cpp src/vocabulary.cpp)