//
//  Created by Ilya Gulkov on 5/7/16 in XCode 6.4 on MacBook Pro Retina 2013 kuplennom za 90k pri starom dalare
//

#include "sorting_algs.h"
#include "stats.h"

#define REPORT_PROGRESS() report_progress()

#define NUM_OF_MEASUREMENTS 1

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

enum sort_mode { random_array, random_array_small, nearly_sorted, reversed, few_unique };

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
    
    REPORT_PROGRESS();
    
    return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

long long *time_algorithm(int *arr, int *sizes, int number_of_sizes, sort_function f_sort)
{
    long long *results = new long long[number_of_sizes];
    
    cout << "Testing on " << number_of_sizes << " sizes from " << sizes[0] << " to " << sizes[number_of_sizes - 1] << "..." << endl;
    
    for(int i = 0; i < number_of_sizes; i++) {
        double sum = 0;
        
        cout << "|" << flush;
        
        for(int j = 0; j < NUM_OF_MEASUREMENTS; j++) {
            sum += time_algorithm_once(arr, sizes[i], f_sort);
            
            cout << "." << flush;
        }
        
        results[i] = sum / NUM_OF_MEASUREMENTS;
    }
    
    cout << endl;
    
    return results;
}

//void time_algorithms(sort_function *fs_sort, int num_algorithms, sort_mode mode, long long *results_table_3d)
//{
//    int *arr = create_array(10000, mode);
//    
//    for(int i = 0; i < num_algorithms; i++) {
//        time_algorithm_100_times_different_sizes(arr, fs_sort[i], results_table_3d + i * 10 * NUM_OF_MEASUREMENTS);
//    }
//    
//    delete[] arr;
//}

int main(int argc, const char * argv[]) {
//    sort_function algs[] = { &bubble_classic, &bubble_tier1, &bubble_tier2, &insertion, &insertion_binary };
//    string names[] = { "Bubble Classic", "Bubble T1", "Bubble T2", "Insertion", "Insertion B" };
    
    int *arr = create_array(100000, random_array);
    int sizes[100] = { 1000 , 2000 , 3000 , 4000 , 5000 , 6000 , 7000 , 8000 , 9000 , 10000 , 11000 , 12000 , 13000 , 14000 , 15000 , 16000 , 17000 , 18000 , 19000 , 20000 , 21000 , 22000 , 23000 , 24000 , 25000 , 26000 , 27000 , 28000 , 29000 , 30000 , 31000 , 32000 , 33000 , 34000 , 35000 , 36000 , 37000 , 38000 , 39000 , 40000 , 41000 , 42000 , 43000 , 44000 , 45000 , 46000 , 47000 , 48000 , 49000 , 50000 , 51000 , 52000 , 53000 , 54000 , 55000 , 56000 , 57000 , 58000 , 59000 , 60000 , 61000 , 62000 , 63000 , 64000 , 65000 , 66000 , 67000 , 68000 , 69000 , 70000 , 71000 , 72000 , 73000 , 74000 , 75000 , 76000 , 77000 , 78000 , 79000 , 80000 , 81000 , 82000 , 83000 , 84000 , 85000 , 86000 , 87000 , 88000 , 89000 , 90000 , 91000 , 92000 , 93000 , 94000 , 95000 , 96000 , 97000 , 98000 , 99000 , 100000 };
    
    time_t start_time = time(NULL);
    
    long long *results = time_algorithm(arr, sizes, 100, &insertion);
    
    cout << endl << "Took " << time(NULL) - start_time << "s" << endl;
    
    ofstream f("/Users/frnkymac/Code/arz/arz_ultimate/pidr.dat", ios::trunc | ios::out);
    
    f << "-" << " " << "bc" << endl;
    
    for(int i = 0; i < 100; i++) {
        f << sizes[i] << " " << results[i] / 1000.0 / 1000.0 << endl;
    }
    
    f.close();
    
    delete[] results;
    delete[] arr;
    
    return 0;
}
