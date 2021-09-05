set(SOURCES
        src/StringHelper.cpp
        )

set(UT_SOURCES
        src/StringHelperTest.cpp
        )

add_library(utils STATIC ${SOURCES})
target_include_directories(utils PUBLIC src ${Boost_INCLUDE_DIR})
target_compile_options(utils PUBLIC ${FLAGS})

add_executable(utilsUT ${UT_SOURCES})
target_include_directories(utilsUT PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(utilsUT PUBLIC gmock_main gtest utils)
target_compile_options(utilsUT PUBLIC ${FLAGS})
add_test(NAME utilsUT COMMAND utilsUT WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
