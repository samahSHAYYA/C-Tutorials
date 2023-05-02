# Adding subdirectories
set(SUB_DIRS test_common test_bst_and_avl)

foreach(SUB_DIR ${SUB_DIRS})
    add_subdirectory(${SUB_DIR})
endforeach()
