cmake_minimum_required(VERSION 3.20)

project(berthier CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  set(FLAGS /std:c++latest /W4 /permissive- /MP)
else()
  add_compile_options(-std=c++2a -Wall -Wextra)
  set(FLAGS -std=c++2a -Wall -Wextra)
endif()

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googlemock/include")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googletest/include")
set(JSON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/json/include")
set(DATE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/date/include")

enable_testing()
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0)
  link_libraries(--coverage)
endif()

add_subdirectory(src)

