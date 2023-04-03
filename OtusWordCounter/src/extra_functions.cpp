#include "extra_functions.h"

#include <algorithm>
#include <iterator>
#include <vector>

#include <iomanip>

std::string tolower(const std::string &str)
{
    std::string lower_str;
    std::transform(
        std::cbegin(str), std::cend(str),
        std::back_inserter(lower_str),
        [](unsigned char ch)
        {
            return std::tolower(ch);
        });
    return lower_str;
};

void count_words(std::istream &stream, Counter &counter)
{
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s)
                  {
                      ++counter[tolower(s)];
                  });
}

void count_words_mutex(std::istream &stream, Counter &counter, std::mutex &mtx)
{
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter, &mtx](const std::string &s)
                  {
                      mtx.lock();
                      ++counter[tolower(s)];
                      mtx.unlock();
                  });
}

void print_topk(std::ostream &stream, const Counter &counter, const size_t k)
{

    if (counter.size() == 0)
    {
        return;
    }

    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it)
    {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k,
        std::end(words),
        [](auto lhs, auto &rhs)
        {
            return lhs->second > rhs->second;
        });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair)
        {
            stream << std::setw(4) << pair->second << " " << pair->first
                   << '\n';
        });
}