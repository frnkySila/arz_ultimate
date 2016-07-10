//
//  Created by Ilya Gulkov on 5/7/16 in XCode 6.4 on MacBook Pro Retina 2013 kuplennom za 90k pri starom dalare
//

#include "sorting_algs.h"
#include "stats.h"

#define REPORT_PROGRESS() report_progress()

#define NUM_OF_MEASUREMENTS 10

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
using namespace std;

int inner_cycles, outer_cycles, comparisons, swaps;

typedef void (*sort_function)(int*, int, int);

void print_array(int *arr, int begin, int end)
{
    for(int i = begin; i < end; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void report_progress()
{
    static int i = 0;
    
    if(++i % 10 == 0) {
        cout << ".";
    }
}

enum sort_mode { random_array, random_array_small, completely_sorted, nearly_sorted, reversed, few_unique };

int *create_array(int size, sort_mode mode)
{
    int *arr = new int[size];
    
    switch (mode) {
        case random_array:
            srand((unsigned int)time(NULL));
            
            for(int i = 0; i < size; i++) {
                arr[i] = rand();
            }
            break;
        case random_array_small:
            srand((unsigned int)time(NULL));
            
            for(int i = 0; i < size; i++) {
                arr[i] = rand() % size;
            }
            break;
        case completely_sorted:
            for(int i = 0; i < size; i++) {
                arr[i] = i;
            }
        case nearly_sorted: // order of N swaps
            for(int i = 0; i < size; i++) {
                arr[i] = i;
            }
            
            srand((unsigned int)time(NULL));
            
            for(int i = 0; i < 2 * size; i++) {
                int j = rand() % (size - 1);
                swap(arr[j], arr[j + 1]);
            }
            break;
        case reversed:
            for(int i = 0; i < size; i++) {
                arr[i] = size - i;
            }
            break;
        case few_unique:
            srand((unsigned int)time(NULL));
            
            for(int i = 0; i < size; i++) {
                arr[i] = rand() % 10;
            }
            break;
    }
    
    return arr;
}

int *create_sizes_linear(int num_sizes, int min, int max)
{
    int *arr = new int[num_sizes];
    
    int difference = (max - min) / num_sizes;
    
    for(int i = 0; i < num_sizes; i++) {
        arr[i] = min + difference * i;
    }
    
    return arr;
}

long long time_algorithm_once(int *arr, int arr_size, sort_function f_sort)
{
    int *newArr = new int[arr_size];
    memcpy(newArr, arr, arr_size * sizeof(int));
    
    auto start_time = chrono::high_resolution_clock::now();
    
    f_sort(newArr, 0, arr_size);
    
    auto end_time = chrono::high_resolution_clock::now();
    
    delete[] newArr;
    
    REPORT_PROGRESS();
    
    return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

long long *time_algorithm(int *arr, int *sizes, int num_sizes, sort_function f_sort)
{
    long long *results = new long long[num_sizes];
    
    cout << "Testing on " << num_sizes << " sizes from " << sizes[0] << " to " << sizes[num_sizes - 1] << "..." << endl;
    
    for(int i = 0; i < num_sizes; i++) {
        double sum = 0;
        
        cout << i + 1 << flush;
        
        for(int j = 0; j < NUM_OF_MEASUREMENTS; j++) {
            sum += time_algorithm_once(arr, sizes[i], f_sort);
            
            cout << "." << flush;
        }
        
        results[i] = sum / NUM_OF_MEASUREMENTS;
    }
    
    cout << endl;
    
    return results;
}

void time_algorithms(sort_mode mode, int *sizes, int num_sizes, sort_function *fs_sort, string *algorithm_names, int num_algorithms)
{
    time_t start_time_total = time(NULL);
    
    int *arr = create_array(sizes[num_sizes - 1], mode);
    long long *results = new long long[num_sizes * num_algorithms];
    
    for(int i = 0; i < num_algorithms; i++) {
        time_t start_time = time(NULL);
        
        long long *current_results = time_algorithm(arr, sizes, num_sizes, fs_sort[i]);
        
        // TODO: Transpose this cycle
        for(int j = 0; j < num_sizes; j++) {
            results[i * num_sizes + j] = current_results[j];
        }
        
        delete[] current_results;
        
        cout << "Took " << time(NULL) - start_time << "s" << endl << endl;
    }
    
    time_t total_time = time(NULL) - start_time_total;
    cout << endl << "All took " << total_time / 60 << ":" << total_time % 60 << "s" << endl;
    
    ofstream f("/Users/frnkymac/Code/arz/arz_ultimate/pidr.dat", ios::trunc | ios::out);
    
    f << "-";
    
    for(int i = 0; i < num_algorithms; i++) {
        f << " " << algorithm_names[i];
    }
    
    f << endl;
    
    for(int i = 0; i < num_sizes; i++) {
        f << sizes[i];
        
        for(int j = 0; j < num_algorithms; j++) {
            f << " " << results[j * num_sizes + i];
        }
        
        f << endl;
    }
    
    f.close();
    
    delete[] results;
    delete[] arr;
}

int main(int argc, const char * argv[]) {
    string names[5] = { "Bubble-Classic", "Bubble-T1", "Bubble-T2", "Insertion", "Insertion-B" };
    sort_function algs[5] = { &bubble_classic, &bubble_tier1, &bubble_tier2, &insertion, &insertion_binary };
    
    int *sizes = create_sizes_linear(25, 1000, 25000);
    
    time_algorithms(few_unique, sizes, 25, algs, names, 5);

    delete[] sizes;
    
    return 0;
}
