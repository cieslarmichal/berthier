if (WIN32)
    set(BOOST_ROOT C:\\libraries\\boost)
endif ()

find_package(Boost REQUIRED)

set(GTEST_ROOT "/home/michal/repos/berthier/externals/googletest" CACHE PATH "Path to googletest")
find_package(GTest REQUIRED)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(json)
add_subdirectory(date)
