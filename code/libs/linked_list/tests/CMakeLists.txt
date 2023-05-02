# Adding subdirectories
set(SUB_DIRS test_common test_unidirectional_and_bidirectional)

foreach(SUB_DIR ${SUB_DIRS})
    add_subdirectory(${SUB_DIR})
endforeach()
