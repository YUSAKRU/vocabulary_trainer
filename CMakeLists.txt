cmake_minimum_required(VERSION 3.5)

project(vocabulary_trainer)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib 4.0 REQUIRED)  # raylib'i ekledik

include_directories(include)

add_executable(vocabulary_trainer src/main.cpp src/vocabulary.cpp)

target_link_libraries(vocabulary_trainer raylib)  # raylib'i bağladık