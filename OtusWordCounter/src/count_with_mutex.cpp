#include "count_functions.h"
#include "extra_functions.h"

#include <vector>
#include <thread>

int count_with_mutex(int argc, char **argv, long long &total_time)
{
    auto start = std::chrono::high_resolution_clock::now(); 

    Counter the_only_dictionary; 
    std::mutex dictionary_mtx;   

    std::vector<std::thread> counting_threads;      
    std::vector<std::ifstream *> input_stream_ptrs; 

    unsigned int threads_number = 0; 

    for (int i = 1; i < argc; ++i)
    {
        std::ifstream *f = nullptr;
        f = new std::ifstream(argv[i]);

        if ((f != nullptr) && (f->is_open()))
        {
            input_stream_ptrs.emplace_back(f);
            counting_threads.emplace_back(count_words_mutex, ref(*f), ref(the_only_dictionary), ref(dictionary_mtx));
            ++threads_number;
        }
        else
        {
            std::cerr << "Failed to open file " << argv[i] << '\n';
        }
    }

    if (threads_number == 0)
    {
        std::cout << "EXIT FAILURE" << std::endl;
        return EXIT_FAILURE;
    }

    for (auto &thread_item : counting_threads)
    {
        thread_item.join();
    }

    for (auto &isptr : input_stream_ptrs)
    {
        delete isptr;
    }

    std::cout << " - WITH MUTEX - " << std::endl;
    print_topk(std::cout, the_only_dictionary, TOPK); 
    std::cout << " -------------- \n"
              << std::endl;

    auto end = std::chrono::high_resolution_clock::now();                                
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 

    total_time = elapsed_ms.count();

    return 0;
}