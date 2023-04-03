#include "count_functions.h"
#include "extra_functions.h"

#include <vector>
#include <thread>
#include <mutex>

int count_sum_map(int argc, char **argv, long long &total_time)
{
    auto start = std::chrono::high_resolution_clock::now(); 

    std::vector<std::thread> counting_threads;      
    std::vector<std::ifstream *> input_stream_ptrs; 
    std::vector<Counter *> counter_ptrs;

    unsigned int threads_number = 0; 

    for (int i = 1; i < argc; ++i)
    {
        std::ifstream *f = nullptr;
        f = new std::ifstream(argv[i]);

        Counter *ctr_ptr = nullptr;
        ctr_ptr = new Counter;

        if ((f != nullptr) && (f->is_open()) && (ctr_ptr != nullptr))
        {
            counter_ptrs.emplace_back(ctr_ptr);
            input_stream_ptrs.emplace_back(f);
            counting_threads.emplace_back(count_words, ref(*f), ref(*ctr_ptr));
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

    Counter final_dictionary; 


    for (auto &cntptr : counter_ptrs)
    {
        if (final_dictionary.empty())
        {
            final_dictionary.merge(*cntptr);
        }
        else
        {
            for (std::map<std::string, std::size_t>::iterator it = cntptr->begin(); it != cntptr->end(); ++it)
            {
                try
                {
                    if (final_dictionary.at(it->first) != 0)
                    {
                        final_dictionary[it->first] = final_dictionary.at(it->first) + it->second;
                    }
                }
                catch (std::out_of_range)
                {
                    final_dictionary[it->first] = it->second;
                }
            }
        }

        delete cntptr;
    }

    std::cout << " -  SUM MAPS - " << std::endl;
    print_topk(std::cout, final_dictionary, TOPK); 
    std::cout << " ------------- \n"
              << std::endl;

    auto end = std::chrono::high_resolution_clock::now();                                 
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 

    total_time = elapsed_ms.count();

    return 0;
}