if (WIN32)
    set(BOOST_ROOT C:\\libraries\\boost)
endif ()

find_package(Boost REQUIRED)

add_subdirectory(googletest)
