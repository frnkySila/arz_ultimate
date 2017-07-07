//
//  sorting_debug.cpp
//  arz_ultimate
//
//  Created by Ilya Gulkov on 11/7/16.
//  Copyright (c) 2016 Ilya Gulkov. All rights reserved.
//

#include "sorting_debug.h"

#include <iostream>
#include <set>

int *create_array(size_t size, sort_mode mode)
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
                arr[i] = rand() % (int)size;
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
                int j = rand() % (int)(size - 1);
                std::swap(arr[j], arr[j + 1]);
            }
            break;
        case reversed:
            for(int i = 0; i < size; i++) {
                arr[i] = (int)size - i;
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

std::vector<size_t> create_sizes_linear(size_t num_sizes, int min, int max)
{
    std::vector<size_t> sizes(num_sizes);
    
    size_t difference = (max - min) / num_sizes;
    
    for(int i = 0; i < num_sizes; i++) {
        sizes[i] = min + difference * i;
    }
    
    return sizes;
}

bool is_sorted(int *arr, int begin, int end)
{
    for(int i = begin; i < end - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            return false;
        }
    }
    
    return true;
}

bool same_elements(int *arr1, int begin1, int *arr2, int begin2, int length)
{
    std::set<int> elems1{}, elems2{};
    
    for(int i = begin1; i < begin1 + length; i++) {
        elems1.insert(arr1[i]);
    }
    
    for(int i = begin2; i < begin2 + length; i++) {
        elems2.insert(arr2[i]);
    }
    
    return elems1 == elems2;
}
