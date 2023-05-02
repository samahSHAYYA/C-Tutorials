cmake_minimum_required(VERSION 3.22)

project(tree_apps
        VERSION 1.0.0
        DESCRIPTION "Provides several interactive binary tree apps."
        LANGUAGES C)

# Adding options regarding building this library as shared or static
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_STATIC_LIBS "Build static library" ON)

# Checking to ensure at least one option is set
if(NOT BUILD_SHARED_LIBS AND NOT BUILD_STATIC_LIBS)
    message(FATAL_ERROR
            "Neither BUILD_SHARED_LIBS nor BUILD_STATIC_LIBS have been enabled
            for building. Please enable at least one of these options."
    )
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Adding executables
set(APP_SRC_FILES
    src/tree_app.c
    src/helpers.c)

set(TARGET_BASENAMES bst avl)

set(tree_lib_LIBRARIES
    tree_lib::tree_lib_static
    tree_lib::tree_lib_shared)

set(installable_targets "")
foreach(TARGET_BASENAME ${TARGET_BASENAMES})
    foreach(LIB_NAME ${tree_lib_LIBRARIES})
            # Find the last index of "_"
            string(FIND ${LIB_NAME} "_" last_index REVERSE)

            # Adding one to the index to start from first charcter after _
            math(EXPR last_index "${last_index} + 1")

            # Extract the substring after the last "_"
            string(SUBSTRING ${LIB_NAME} ${last_index} -1 LIB_TYPE)

            # Setting target name
            set(TARGET_NAME ${TARGET_BASENAME}_${LIB_TYPE}_app)

            # Creating target
            add_executable(${TARGET_NAME})

            # Setting private sources and include directory
            target_sources(${TARGET_NAME} PRIVATE ${APP_SRC_FILES})

            target_include_directories(${TARGET_NAME} PRIVATE include)

            # Linking to tree_lib
            target_link_libraries(${TARGET_NAME} ${LIB_NAME})

            # Setting private target compile definitions in case of
            # building bidirectional app
            if(TARGET_BASENAME STREQUAL "avl")
                    # This allows inclusion of avl header instead of default
                    # bst one
                    target_compile_definitions(${TARGET_NAME}
                                                PRIVATE
                                                    AVL
                    )
            endif()

            # Adding the target to installable targets list
            list(APPEND installable_targets ${TARGET_NAME})
    endforeach()
endforeach()

# Installing the executables
install(TARGETS ${installable_targets}
        RUNTIME DESTINATION bin
)
