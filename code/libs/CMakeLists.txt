# Adding subdirectories
set(SUB_DIRS linked_list tree)

foreach(SUB_DIR ${SUB_DIRS})
    add_subdirectory(${SUB_DIR})
endforeach()
