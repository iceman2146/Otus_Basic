#pragma once
#include <vector>
#include <algorithm>

#include "baseStatistic.h"

class Pct90 : public IStatistics
{
public:
    Pct90() : input_arr{} {}

    void update(double next) override
    {
        input_arr.push_back(next);
    }
    void Sort()
    {
        std::sort(input_arr.begin(), input_arr.end());
    }

    double eval() const override
    {

        if (std::is_sorted(input_arr.begin(), input_arr.end()))
        {

            const auto var_count = static_cast<size_t>(0.9 * input_arr.size());
            return input_arr[var_count];
        }
        else
        {

            std::vector<double> temp_arr = input_arr;
            std::sort(temp_arr.begin(), temp_arr.end());
            const auto var_count = static_cast<size_t>(0.9 * temp_arr.size());
            return temp_arr[var_count];
        }
    }

    const char *name() const override
    {
        return "pct90";
    }

private:
    std::vector<double> input_arr;
};

class Pct95 : public IStatistics
{
public:
    Pct95() : input_arr{} {}

    void update(double next) override
    {
        input_arr.push_back(next);
    }

    double eval() const override
    {
        if (std::is_sorted(input_arr.begin(), input_arr.end()))
        {

            const auto var_count = static_cast<size_t>(0.95 * input_arr.size());
            return input_arr[var_count];
        }
        else
        {

            std::vector<double> temp_arr = input_arr;
            std::sort(temp_arr.begin(), temp_arr.end());
            const auto var_count = static_cast<size_t>(0.95 * temp_arr.size());
            return temp_arr[var_count];
        }
    }

    const char *name() const override
    {
        return "pct95";
    }

private:
    std::vector<double> input_arr;
};