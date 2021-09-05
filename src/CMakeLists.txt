
add_subdirectory(utils)
add_subdirectory(bank)

add_executable(berthier Main.cpp)
target_link_libraries(berthier PRIVATE cpr::cpr)
