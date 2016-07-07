//
//  Created by Ilya Gulkov on 5/7/16 in XCode 6.4 on MacBook Pro Retina 2013 kuplennom za 90k pri starom dalare
//

#include "sorting_algs.h"
#include "stats.h"

#define NUM_OF_MEASUREMENTS 1

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
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

enum sort_mode {manual_entry, random_array, nearly_sorted, reversed, few_unique};

int *create_array(int size, sort_mode mode)
{
    int *arr = new int[size];
    
    switch (mode) {
        case manual_entry:
            for(int i = 0; i < size; i++) {
                cin >> arr[i];            }
            break;
        case random_array:
            srand((unsigned int)time(NULL));
            
            for(int i = 0; i < size; i++) {
                arr[i] = rand();
            }
            break;
        case nearly_sorted: // order of N swaps
            for(int i = 0; i < size; i++) {
                arr[i] = i;
            }
            
            srand((unsigned int)time(NULL));
            
            for(int i = 0; i < size; i++) {
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

long long time_algorithm_once(int *arr, int arr_size, sort_function f_sort)
{
    int *newArr = new int[arr_size];
    memcpy(newArr, arr, arr_size * sizeof(int));
    
    auto start_time = chrono::high_resolution_clock::now();
    
    f_sort(newArr, 0, arr_size);
    
    auto end_time = chrono::high_resolution_clock::now();
    
    delete[] newArr;
    
    return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

void time_algorithm_many_times(int *arr, int arr_size, sort_function f_sort, long long *results, int number_of_times)
{
    for(int i = 0; i < number_of_times; i++) {
        results[i] = time_algorithm_once(arr, arr_size, f_sort);
    }
}

void time_algorithm_100_times_different_sizes(int *arr, sort_function f_sort, long long *results_table_2d)
{
    for(int i = 0; i < 10; i++) {
        int masik_size = 1000 + 1000 * i;
        time_algorithm_many_times(arr, masik_size, f_sort, results_table_2d + (NUM_OF_MEASUREMENTS * i), NUM_OF_MEASUREMENTS);
    }
}

void time_algorithms(sort_function *fs_sort, int num_algorithms, sort_mode mode, long long *results_table_3d)
{
    int *arr = create_array(10000, mode);
    
    for(int i = 0; i < num_algorithms; i++) {
        time_algorithm_100_times_different_sizes(arr, fs_sort[i], results_table_3d + i * 10 * NUM_OF_MEASUREMENTS);
    }
    
    delete[] arr;
}

void print_table_3d(long long *results_table_3d)
{
    cout << setw(4) << "" << setw(11) << "bc" << setw(11) << "b1" << setw(11) << "b2" << setw(11) << "i" << setw(11) << "ib" << endl;
    
    for(int i = 0; i < 10; i++) {
        cout << setw(3) << i + 1 << "k";
        
        for(int j = 0; j < 5; j++) {
            cout << setw(8) << array_avg(results_table_3d + (j * 10 * NUM_OF_MEASUREMENTS + i * NUM_OF_MEASUREMENTS), NUM_OF_MEASUREMENTS) / 1000 << "mcs";
        }
        
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    sort_function algs[] = { &bubble_classic, &bubble_tier1, &bubble_tier2, &insertion, &insertion_binary };
    
    long long *results_table_3d = new long long[10 * NUM_OF_MEASUREMENTS * 5];
    
    time_algorithms(algs, 5, nearly_sorted, results_table_3d);
    
    print_table_3d(results_table_3d);
    
    delete[] results_table_3d;
    
    return 0;
}
