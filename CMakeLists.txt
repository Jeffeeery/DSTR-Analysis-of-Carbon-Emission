cmake_minimum_required(VERSION 3.10)
project(CarbonEmissionAnalysis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Program 1 - Array based
add_executable(program1
    program1_array/main_array.cpp
    program1_array/arraylist.cpp
    program1_array/array_sort.cpp
    program1_array/array_search.cpp
    shared/csvloader.cpp
    shared/analysis.cpp
)

target_include_directories(program1 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/program1_array
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
)

# Program 2 - Linked List based
add_executable(program2
    program2_linkedlist/main_linkedlist.cpp
    program2_linkedlist/linkedlist.cpp
    program2_linkedlist/linkedlist_sort.cpp
    program2_linkedlist/linkedlist_search.cpp
    shared/csvloader.cpp
    shared/analysis.cpp
)

target_include_directories(program2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/program2_linkedlist
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
)
