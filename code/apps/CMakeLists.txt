# Adding subdirectories
set(SUB_DIRS list_apps tree_apps)

foreach(SUB_DIR ${SUB_DIRS})
    add_subdirectory(${SUB_DIR})
endforeach()
