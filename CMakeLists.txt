cmake_minimum_required(VERSION 3.10)
project(wwa-engine)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)
