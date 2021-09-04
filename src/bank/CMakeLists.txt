set(SOURCES
        src/storage/TransactionDb.cpp
        src/storage/MongoDb.cpp
        )

set(UT_SOURCES
        src/storage/TransactionDbTest.cpp
        src/storage/MongoDbTest.cpp
        )

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

add_library(bank ${SOURCES})
#target_link_libraries(bank ${LIBMONGOCXX_LIBRARIES})
#target_link_libraries(bank ${LIBBSONCXX_LIBRARIES})
target_include_directories(bank PUBLIC src)
target_compile_options(bank PUBLIC -std=c++2b -Wall -Wextra)

add_executable(bankUT ${UT_SOURCES})
target_link_libraries(bankUT PUBLIC gmock_main gtest bank)
target_compile_options(bankUT PUBLIC -std=c++2b -Wall -Wextra)
add_test(NAME bankUT COMMAND bankUT WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

