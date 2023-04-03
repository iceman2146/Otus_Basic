cmake_minimum_required(VERSION 3.5)
project(ContainerPRJ)

add_executable(main 
main.cpp
"SequenceContainer.h"
"OneWayList.h"
"TwoWayList.h"
)


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(main PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(main PRIVATE
        /EHa
        /W4
        /WX
    )
endif()
set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
