//
//  Created by Ilya Gulkov on 5/7/16 in XCode 6.4 on MacBook Pro Retina 2013 kuplennom za 90k pri starom dalare
//

#include "sorting_algs.h"
#include "sorting_debug.h"

#define NUM_OF_MEASUREMENTS 1000

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>

typedef void (*sort_function)(int*, int, int);

long long time_algorithm_once(int *arr, size_t arr_size, sort_function f_sort)
{
    int *newArr = new int[arr_size];
    memcpy(newArr, arr, arr_size * sizeof(int));
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    f_sort(newArr, 0, arr_size); // TODO: change all sort functions to accept size_t
    
    auto end_time = std::chrono::high_resolution_clock::now();
    
    delete[] newArr;
    
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
}

long long *time_algorithm(int *arr, std::vector<size_t> sizes, sort_function f_sort)
{
    long long *results = new long long[sizes.size()];

    std::cout << "Testing " << NUM_OF_MEASUREMENTS << " times on " << sizes.size() << " sizes from " << sizes[0]
              << " to " << sizes[sizes.size() - 1] << "..." << std::endl;
    
    for(int i = 0; i < sizes.size(); i++) {
        results[i] = 0;
    }
    
    for(int i = 0; i < NUM_OF_MEASUREMENTS; i++) {
        std::cout << i + 1 << std::flush;
        
        for(int j = 0; j < sizes.size(); j++) {
            results[j] += time_algorithm_once(arr, sizes[j], f_sort);

            std::cout << "." << std::flush;
        }

        std::cout << " ";
    }

    std::cout << std::endl;
    
    for(int i = 0; i < sizes.size(); i++) {
        results[i] = results[i] / NUM_OF_MEASUREMENTS;
    }
    
    return results;
}

void time_algorithms(sort_mode mode, std::vector<size_t> sizes, sort_function *fs_sort, std::string *algorithm_names, int num_algorithms)
{
    time_t start_time_total = time(NULL);
    
    int *arr = create_array(sizes[sizes.size() - 1], mode);
    long long *results = new long long[sizes.size() * num_algorithms];
    
    for(int i = 0; i < num_algorithms; i++) {
        time_t start_time = time(NULL);
        
        long long *current_results = time_algorithm(arr, sizes, fs_sort[i]);
        
        for(int j = 0; j < sizes.size(); j++) {
            results[i * sizes.size() + j] = current_results[j];
        }
        
        delete[] current_results;

        std::cout << "Took " << time(NULL) - start_time << "s" << std::endl << std::endl;
    }
    
    time_t total_time = time(NULL) - start_time_total;
    std::cout << std::endl << "All took " << total_time / 60 << ":" << total_time % 60 << std::endl;

    std::ofstream f("/Users/frnkymac/Code/arz/arz_ultimate/pidr.dat", std::ios::trunc | std::ios::out);
    
    f << "-";
    
    for(int i = 0; i < num_algorithms; i++) {
        f << " " << algorithm_names[i];
    }
    
    f << std::endl;
    
    for(int i = 0; i < sizes.size(); i++) {
        f << sizes[i];
        
        for(int j = 0; j < num_algorithms; j++) {
            f << " " << results[j * sizes.size() + i];
        }
        
        f << std::endl;
    }
    
    f.close();
    
    delete[] results;
    delete[] arr;
}

int main(int argc, const char * argv[]) {
    std::string names[5] = { "Bubble-T2", "Insertion", "Insertion-B", "Shell", "Merge" };
    sort_function algs[5] = { &bubble_tier2, &insertion, &insertion_binary, &shell, &merge_sort };

    time_algorithms(random_array, create_sizes_linear(25, 100, 10000), algs, names, 5);
    
    return 0;
}
