// Read files and prints top k word by frequency

#include <cctype>
#include <cstdlib>

#include "extra_data.h"
#include "extra_functions.h"
#include "count_functions.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    long long time_one_thread = 0;
    long long time_mutex = 0;
    long long time_sum_map = 0;

    int result = 0;

    //
    result = count_one_thread(argc, argv, time_one_thread);

    //
    result = count_with_mutex(argc, argv, time_mutex);

    //
    result = count_sum_map(argc, argv, time_sum_map);

    std::cout << "dT in one thread " << time_one_thread / 1000000 << " s\n";
    std::cout << "dT with mutex    " << time_mutex / 1000000 << " s\n";
    std::cout << "dT sum map  " << time_sum_map / 1000000 << " s\n";
}
