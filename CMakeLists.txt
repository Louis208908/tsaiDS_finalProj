cmake_minimum_required(VERSION 3.10.2)
project(FINAL_PROJ)


macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()
#把cmake 的variables 都顯示出來
# print_all_variables() 要使用的時候call這個
# message(STATUS "project source dir = ${FINAL_PROJ_SOURCE_DIR}")
# print 出 FINAL_PROJ_SOURCE_DIR 的內容

include_directories(include)
include_directories(src)
#引入需要的資料夾


# option(BUILD_SHARED_LIBS ON)
set(EXECUTABLE_OUTPUT_PATH ${FINAL_PROJ_SOURCE_DIR}/src)
# set(EXECUTABLE_OUTPUT_PATH src)
set(LIBRARY_OUTPUT_PATH ${FINAL_PROJ_SOURCE_DIR}/include/lib)
#把編譯完的檔案輸出到src









# if(BUILD_SHARED_LIBS)
    add_library(
            map_lib 
            ${FINAL_PROJ_SOURCE_DIR}/include/map.cpp
    )

    add_library(
            rental_lib 
            ${FINAL_PROJ_SOURCE_DIR}/include/rental.cpp
            ${FINAL_PROJ_SOURCE_DIR}/include/bike.cpp
    )

    add_library(
            renter_lib 
            ${FINAL_PROJ_SOURCE_DIR}/include/renter.cpp
    )
#     add_library(
#             avl_treeLib SHARED
#             ${tree_SOURCE_DIR}/src/avl_tree.c
#     )
# else()
#     add_library(
#             bst_treeLib 
#             ${tree_SOURCE_DIR}/src/bst_tree.c
#     )
#     add_library(
#             avl_treeLib SHARED
#             ${tree_SOURCE_DIR}/src/avl_tree.c
#     )
# endif()
#製作函式庫

add_executable(
            107033237_proj
            ${FINAL_PROJ_SOURCE_DIR}/src/107033237_proj.cpp
)
# add_executable(
#             avl 
#             #${tree_SOURCE_DIR}/include/tree.h
#             ${tree_SOURCE_DIR}/src/avl.c
# )
#做出主程式執行檔
    
target_link_libraries(107033237_proj map_lib rental_lib renter_lib)
# target_link_libraries(bst bst_treeLib) 
# target_link_libraries(avl avl_treeLib) 
# #將主程式跟函式庫連結在一起
