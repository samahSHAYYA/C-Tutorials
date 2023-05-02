# Adding tests for "unidirectional.h" and "bidirectional.h"
if(${PROJECT_IS_TOP_LEVEL})
    # This is top level project.
    set(TEST_BASE_NAME test)
else()
    # This is s subproject. In this case, we add project name to avoid naming
    # conflicts.
    set(TEST_BASE_NAME test_${PROJECT_NAME})
endif()

set(LIST_TYPES unidirectional bidirectional)
set(ORDER_TYPES unordered ordered)
set(APPROACHES iterative recursive)

foreach(LIST_TYPE ${LIST_TYPES})
    foreach(ORDER_TYPE ${ORDER_TYPES})
        foreach(APPROACH ${APPROACHES})
            set(TEST_NAME ${TEST_BASE_NAME}_${ORDER_TYPE}_${LIST_TYPE}_${APPROACH})

            # Adding test and linking it to project sttaic library and unity
            add_executable(${TEST_NAME}
                           test_unidirectional_and_bidirectional.c)

            target_link_libraries(${TEST_NAME}
                                  ${PROJECT_NAME}_static
                                  unity
            )

            if(LIST_TYPE STREQUAL "bidirectional")
                # Add private compile definitions: BIDIRECTIONAL is a macro
                # added in test_unidirectional_and_bidirectional.c file to
                # signal inclusion of "bidirectional.h" instead of
                # "unidirectional.h", which is the default inclusion choice.
                target_compile_definitions(${TEST_NAME}
                                           PRIVATE
                                                BIDIRECTIONAL
                )
            endif()

            set(ARGS "")
            if(ORDER_TYPE STREQUAL "ordered")
                list(APPEND ARGS "--ordered")
            endif()

            if(APPROACH STREQUAL "recursive")
                list(APPEND ARGS "--recursive")
            endif()

            add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} ${ARGS})
            endforeach()
    endforeach()
endforeach()
