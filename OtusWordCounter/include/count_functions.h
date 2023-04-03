#pragma once

#include "extra_data.h"

#include <fstream>
#include <chrono>
#include <iostream>

int count_one_thread(int argc, char **argv, long long &total_time);

int count_with_mutex(int argc, char **argv, long long &total_time);

int count_sum_map(int argc, char **argv, long long &total_time);
