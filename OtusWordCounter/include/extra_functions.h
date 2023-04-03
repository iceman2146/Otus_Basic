#pragma once

#include "extra_data.h"

#include <mutex>

std::string tolower(const std::string &str);

void count_words(std::istream &stream, Counter &);

void count_words_mutex(std::istream &stream, Counter &counter, std::mutex &mtx);

void print_topk(std::ostream &stream, const Counter &, const size_t k);
