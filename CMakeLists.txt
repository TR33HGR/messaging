cmake_minimum_required(VERSION 3.29.2)
project(Messaging LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Builds unittests in tests folder" ON)

add_subdirectory(src)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
