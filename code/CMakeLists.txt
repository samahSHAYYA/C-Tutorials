cmake_minimum_required(VERSION 3.22)

project(C_Tutorials
        VERSION 1.0.0
        DESCRIPTION "It implements linked lists and binary trees."
        LANGUAGES C
)

# Options to build shared and static libraries
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_STATIC_LIBS "Build static libraries" ON)

# Option to build documentation (it is good to update documentation although
# it might take some considerable time)
option(BUILD_DOCS "Build documentation" ON)

# Option to build tests (it is good to build and run tests although it might
# take some considerable time)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Adding subdirectories (excluding tests as it is treated separately)
set(SUB_DIRS apps libs)

foreach(SUB_DIR ${SUB_DIRS})
    add_subdirectory(${SUB_DIR})
endforeach()

# Adding dependencies particularly Unity for testing
add_library(unity
            STATIC
                deps/unity/src/unity.c
                deps/unity/extras/fixture/src/unity_fixture.c
                deps/unity/extras/memory/src/unity_memory.c
)

# We link to unity as interface as to indicate that the project does not need
# to build Unity as a part of the project (we mention only the parts that we
# will using corresponding to "unity.h" usual case and the extras here to be
# able to use "unity_fixture.h")
target_include_directories(unity
                           PUBLIC
                                deps/unity/src
                                deps/unity/extras/fixture/src
                                deps/unity/extras/memory/src
)

# Linking Unity to threads to bea ble to run tests in parallel
if(WIN32)
    # Windows systems
    target_link_libraries(unity PRIVATE winpthread)
else()
    # Unix-like Systems (Threads is acually pthread on Unix-like systems)
    find_package(Threads REQUIRED)
    target_link_libraries(unity PRIVATE ${CMAKE_THREAD_LIBS_INIT})
endif()
