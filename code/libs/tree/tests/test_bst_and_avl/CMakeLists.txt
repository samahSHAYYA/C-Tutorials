# Adding tests for "bst.h" and "avl.h"

if(${PROJECT_IS_TOP_LEVEL})
    # This is top level project.
    set(TEST_BASE_NAME test)
else()
    # This is s subproject. In this case, we add project name to avoid naming
    # conflicts.
    set(TEST_BASE_NAME test_${PROJECT_NAME})
endif()

set(TREE_TYPES bst avl)
set(APPROACHES iterative recursive)

foreach(TREE_TYPE ${TREE_TYPES})
    foreach(APPROACH ${APPROACHES})
        set(TEST_NAME ${TEST_BASE_NAME}_${TREE_TYPE}_${APPROACH})

        # Adding test and linking it to project sttaic library and unity
        add_executable(${TEST_NAME} test_bst_and_avl.c)

        target_link_libraries(${TEST_NAME}
                                ${PROJECT_NAME}_static
                                unity
        )

        if(TREE_TYPE STREQUAL "avl")
            # Add private compile definitions: AVL is a macro added in
            # test_bst_avl.c file to signal inclusion of "avl.h" instead of
            # "bst.h", which is the default inclusion choice.
            target_compile_definitions(${TEST_NAME}
                                       PRIVATE
                                            AVL
            )
        endif()

        set(ARGS "")

        if(APPROACH STREQUAL "recursive")
            list(APPEND ARGS "--recursive")
        endif()

        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} ${ARGS})
    endforeach()
endforeach()
