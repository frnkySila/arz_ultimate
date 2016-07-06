//
//  Created by Ilya Gulkov on 5/7/16 in XCode 6.4 on MacBook Pro Retina 2013 kuplennom za 90k pri starom dalare
//

#include "sorting_algs.h"

#include <iostream>
#include <cstdlib>
#include <chrono>
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
    memccpy(newArr, arr, arr_size, sizeof(int));
    
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

int main(int argc, const char * argv[]) {
    int *arr = create_array(10000, nearly_sorted);
    
    long long *results = new long long[100];
    
    time_algorithm_many_times(arr, 10000, &bubble_classic, results, 100);
    
    for(int i = 0; i < 100; i++) {
        cout << results[i] << endl;
    }
    
    delete[] results;
    
    delete[] arr;
    
    return 0;
}
