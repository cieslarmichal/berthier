set(SOURCES
        dummy.cpp
        )

set(UT_SOURCES
        dummy.cpp
        )

add_library(bank STATIC ${SOURCES})
target_link_libraries(bank ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(bank ${LIBBSONCXX_LIBRARIES})
target_include_directories(bank PUBLIC src)

add_executable(bankUT ${UT_SOURCES})
target_link_libraries(bankUT PUBLIC gmock_main gtest bank)
add_test(NAME bankUT COMMAND bankUT WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

