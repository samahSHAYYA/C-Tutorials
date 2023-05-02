cmake_minimum_required(VERSION 3.22)

# Note that we always use underscored project lower-case names (instead of
# hyphened ones) to avoid potential conflicts (consider it as a best practice)
project(tree_lib
        VERSION 1.0.0
        DESCRIPTION "Provides binary tree data structures and functions."
        LANGUAGES C
)

# Setting language standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Adding global options regarding building libraries, documentation and tests
if (NOT DEFINED BUILD_SHARED_LIBS)
    option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif()

if (NOT DEFINED BUILD_STATIC_LIBS)
    option(BUILD_STATIC_LIBS "Build static libraries" ON)
endif()

if (NOT DEFINED BUILD_DOCS)
    option(BUILD_DOCS "Build documentation" ON)
endif()

if(NOT DEFINED BUILD_TESTS)
    option(BUILD_TESTS "Build tests" ON)
endif()

# Adding options that are particulary intended for this project that can
# override the above global all libraries, documentation and tests options
# (specific options will be toggled by global ones until they are explicitly
# set / defined by the user)
# NB: CMAKE_SOURCE_DIR holds the root cmake project directory and does not
# change within sub--projects
include(${CMAKE_SOURCE_DIR}/cmake/FollowerOption.cmake)

define_follower_option(BUILD_SHARED_LIBS
                      ${PROJECT_NAME}_BUILD_SHARED
                      "Build shared ${PROJECT_NAME}"
)

define_follower_option(BUILD_STATIC_LIBS
                      ${PROJECT_NAME}_BUILD_STATIC
                      "Build static ${PROJECT_NAME}"
)

define_follower_option(BUILD_DOCS
                      ${PROJECT_NAME}_BUILD_DOCS
                      "Build ${PROJECT_NAME} documentation"
)

define_follower_option(BUILD_TESTS
                      ${PROJECT_NAME}_BUILD_TESTS
                      "Build ${PROJECT_NAME} tests"
)

if(${PROJECT_IS_TOP_LEVEL})
    # Hide the specific project options
    mark_as_advanced(${PROJECT_NAME}_BUILD_SHARED
                     ${PROJECT_NAME}_BUILD_STATIC
                     ${PROJECT_NAME}_BUILD_DOCS
                     ${PROJECT_NAME}_BUILD_TESTS)

    set(DOCS_TARGET_NAME docs)
    set(CPACK_BASE_NAME "_")
else()
    set(DOCS_TARGET_NAME ${PROJECT_NAME}_docs)
    set(CPACK_BASE_NAME "_${PROJECT_NAME}_")
endif()

# Setting the corresponding build type options
if(WIN32)
    # Windows debug flag is /Zi
    set(CMAKE_C_FLAGS_RELEASE "/O2")
    set(CMAKE_C_FLAGS_DEBUG "/Zi")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/O2 /Zi")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Os")
else()
    # Unix debug flag is -g
    set(CMAKE_C_FLAGS_RELEASE "-O2")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os")
endif()

# Setting postfixes corresponding to their build type
set(CMAKE_DEBUG_POSTFIX "_dbg")
set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_RELWITHDEBINFO_POSTFIX "_reldbg")
set(CMAKE_MINSIZEREL_POSTFIX "_minszrel")

# Setting the default build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build (choose one of these: Debug, Release,
        RelWithDebInfo, MinSizeRel)" FORCE)
endif()

# Checking to assure at least one build type is set
if(NOT ${PROJECT_NAME}_BUILD_SHARED AND NOT ${PROJECT_NAME}_BUILD_STATIC)
       message(FATAL_ERROR
               "Neither ${PROJECT_NAME}_BUILD_SHARED nor
                ${PROJECT_NAME}_BUILD_STATIC have been enabled for building.
                Please set at least one of them. If you have not manually set
                them, check that at least BUILD_SHARED_LIBS or BUILD_STATIC_LIBS
                is set."
       )
endif()

# Setting shared and sttci library prefixes to empty string (this prevents
# adding the default "lib" at the beginning oeach library name e.g.
# lib<target_output_name>.so or lib<target_output_name>.a).
# Note that you can override the value set here by manually adding PREFIX
# in target properties.
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# Creating list of library source files
set(LIB_SRC_FILES
    src/avl.c
    src/bst.c
    src/common.c
)

set(installable_targets)

if(${PROJECT_NAME}_BUILD_SHARED)
    # Enable Position-Independent Code (PIC) for shared library:
    # This tells the compiler to generate code that does not rely on specific
    # memory addresses, but instead uses relative addressing, allowing the
    # library to work correctly regardless of where it is loaded in memory.
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    add_library(${PROJECT_NAME}_shared SHARED)

    target_sources(${PROJECT_NAME}_shared
                   PRIVATE
                        ${LIB_SRC_FILES})

    # Adding a namespaced alias for the shared library
    add_library(${PROJECT_NAME}::${PROJECT_NAME}_shared
                ALIAS
                ${PROJECT_NAME}_shared)

    target_include_directories(${PROJECT_NAME}_shared
                               PUBLIC
                                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    set_target_properties(${PROJECT_NAME}_shared
                          PROPERTIES
                          OUTPUT_NAME ${PROJECT_NAME}
    )

    if(WIN32)
        set_target_properties(${PROJECT_NAME}_shared
                              PROPERTIES
                              WINDOWS_EXPORT_ALL_SYMBOLS ON)
    endif()

    list(APPEND installable_targets ${PROJECT_NAME}_static)
endif()

if(${PROJECT_NAME}_BUILD_STATIC)
    add_library(${PROJECT_NAME}_static STATIC)

    target_sources(${PROJECT_NAME}_static
                   PRIVATE
                        ${LIB_SRC_FILES})

    # Adding a namespaced alias for the static library
    add_library(${PROJECT_NAME}::${PROJECT_NAME}_static ALIAS ${PROJECT_NAME}_static)

    target_include_directories(${PROJECT_NAME}_static
                               PUBLIC
                                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    set_target_properties(${PROJECT_NAME}_static
                          PROPERTIES
                          OUTPUT_NAME ${PROJECT_NAME}
    )

    list(APPEND installable_targets ${PROJECT_NAME}_shared)
endif()

# Building documentation based on Doxygen
if(${PROJECT_NAME}_BUILD_DOCS)
    find_package(Doxygen)

    if(DOXYGEN_FOUND)
        # Setting doxygen project name in upper case
        string(TOUPPER ${PROJECT_NAME} DOXY_PROJECT_NAME)

        set(DOXY_OUTPUT_REL_PATH docs)
        set(DOXY_GENERATE_MAN YES)     # NB: YES/NO are only allowed in Doxygen
        set(DOXY_MAN_REL_PATH  man)

        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})

        # Adding documentation target (you can generate docs by writing:
        # make docs if it root project else make tree_lib_docs if it is
        # a subproject)
        add_custom_target(${DOCS_TARGET_NAME}
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM  # To execute command as it is (similar to raw expression)
        )

        # Adding clean documentation target (you can clean docs by writing:
        # make clean_docs if it is root project else write:
        # make clean_tree_lib_docs, which is the case of subproject)
        add_custom_target(clean_${DOCS_TARGET_NAME}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/${DOXY_OUTPUT_REL_PATH}
            COMMENT "Cleaning documentation"
        )
    else()
        message(WARNING
                "${PROJECT_NAME}_BUILD_DOCS is ON but Doxygen is not found.
                 ${PROJECT_NAME} documentation generation will be skipped!"
        )
    endif()
endif()

# Installing CMake package configuration files
install(TARGETS ${installable_targets}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION include
)

# Installing headers
set(CMAKE_INSTALL_INCLUDEDIR "include")
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Create package configuration file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion
)

configure_file(${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
               ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
)

# Install package configuration files
install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Optional: Installing documentation
if (${PROJECT_NAME}_BUILD_DOCS AND DOXYGEN_FOUND)
    set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_PREFIX}/${DOXY_OUTPUT_REL_PATH})

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            DESTINATION ${CMAKE_INSTALL_DOCDIR})

    set(DOXYGEN_HTML_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/${DOXY_OUTPUT_REL_PATH}/html)

    if(WIN32)
        install(DIRECTORY ${DOXYGEN_HTML_DIR}
                DESTINATION ${CMAKE_INSTALL_DOCDIR})
    else()
        install(DIRECTORY ${DOXYGEN_HTML_DIR}
                DESTINATION share/${DOXY_OUTPUT_REL_PATH}/${PROJECT_NAME})

        # Optionally, you can also install the generated man pages
        if(${DOXY_GENERATE_MAN})
            set(DOXYGEN_MAN_DIR
                ${CMAKE_CURRENT_BINARY_DIR}/${DOXY_OUTPUT_REL_PATH}/man)

            install(DIRECTORY ${DOXYGEN_MAN_DIR}
                    DESTINATION share)
        endif()
    endif()
endif()

# Testing
if (${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(tests)
endif()

# Adding CPack configuration
set(CPACK${CPACK_BASE_NAME}PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK${CPACK_BASE_NAME}PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK${CPACK_BASE_NAME}PACKAGE_DESCRIPTION_SUMMARY "Binary Tree Library")
set(CPACK${CPACK_BASE_NAME}DEBIAN_PACKAGE_MAINTAINER "Samah A. SHAYYA")

# You can add vendor data
# set(CPACK${CPACK_BASE_NAME}PACKAGE_VENDOR "Add your vendor info")
# set(CPACK${CPACK_BASE_NAME}PACKAGE_CONTACT "Add your contact info")

# Set the package type based on the platform
if(WIN32)
    set(CPACK${CPACK_BASE_NAME}GENERATOR "ZIP")
elseif(UNIX)
    # MacOS or Linux
    set(CPACK${CPACK_BASE_NAME}GENERATOR "TGZ;DEB;RPM")

    # Used for RPM only to allow relocatable paths
    set(CPACK${CPACK_BASE_NAME}RPM_PACKAGE_RELOCATABLE ON)
    set(CPACK${CPACK_BASE_NAME}RPM_RELOCATION_PATHS "${CMAKE_INSTALL_PREFIX}")
endif()

# Including CPack after setting CPack configuration
include(CPack)
