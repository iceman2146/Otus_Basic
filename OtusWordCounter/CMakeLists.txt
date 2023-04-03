cmake_minimum_required(VERSION 3.5)

project(WordFinder CXX)

add_executable(
    WordFinder
    src/main.cpp
    src/count_single_thread.cpp 
    src/count_with_mutex.cpp 
    src/count_sum_map.cpp
    src/extra_functions.cpp
    )
target_include_directories(WordFinder PRIVATE include)


set_target_properties(WordFinder PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

