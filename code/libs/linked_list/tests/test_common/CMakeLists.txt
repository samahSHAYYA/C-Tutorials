# Adding test for "common.h"

if(${PROJECT_IS_TOP_LEVEL})
    # This is top level project.
    set(TEST_NAME test_common)
else()
    # This is s subproject. In this case, we add project name to avoid naming
    # conflicts.
    set(TEST_NAME test_${PROJECT_NAME}_common)
endif()

add_executable(${TEST_NAME} test_common.c)

target_link_libraries(${TEST_NAME} ${PROJECT_NAME}_static unity)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
