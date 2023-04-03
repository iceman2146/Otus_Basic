#include "count_functions.h"
#include "extra_functions.h"

int count_one_thread(int argc, char **argv, long long &total_time)
{
    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;
    for (int i = 1; i < argc; ++i)
    {
        std::ifstream input{argv[i]};
        if (!input.is_open())
        {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;
        }
        count_words(input, freq_dict);
    }

    std::cout << " - Single thread - " << std::endl;
    print_topk(std::cout, freq_dict, TOPK);
    std::cout << " -------------- \n"
              << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    total_time = elapsed_ms.count();

    return 0;
}