cmake_minimum_required(VERSION 3.5)

project(Statist)

add_executable(statistics 
statistics.cpp
"arSrednee_and_sredneKvadraticheskoe.h"
"baseStatistic.h"
"min_max.h"
"procentil.h"
)

set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

