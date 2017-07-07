//
//  sorting_algs.cpp
//  arz_ultimate
//
//  Created by Ilya Gulkov on 7/7/16.
//  Copyright (c) 2016 Ilya Gulkov. All rights reserved.
//

#include "sorting_algs.h"

#include <iostream>

void bubble_classic(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++)
    {
        for(int j = begin; j < end - i; j++) {
            if(arr[j] > arr[j+1])
            {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

void bubble_tier1(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++)
    {
        bool already_sorted = true;
        
        for(int j = begin; j < end - i; j++) {
            if(arr[j] > arr[j+1])
            {
                std::swap(arr[j], arr[j+1]);
                
                already_sorted = false;
            }
        }
        
        if(already_sorted) break;
    }
}

void bubble_tier2(int *arr, int begin, int end)
{
    int last_swap = end - 1;
    
    do
    {
        int new_last_swap = 0;
        
        for(int j = begin; j < last_swap; j++) {
            if(arr[j] > arr[j+1])
            {
                std::swap(arr[j], arr[j+1]);
                
                new_last_swap = j;
            }
        }
        
        last_swap = new_last_swap;
        
    } while(last_swap != 0);
}

void insertion(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++) {
        int new_position = 0;
        
        for(int j = i - 1; j >= 0; j--) {
            if(arr[j] <= arr[i]) {
                new_position = j + 1;
                break;
            }
        }
        
        int temp = arr[i];
        for(int j = i; j > new_position; j--) {
            arr[j] = arr[j - 1];
        }
        arr[new_position] = temp;
    }
}

inline int binary_search(int *arr, int begin, int end, int target)
{
    while(begin - end < -1) {
        int mid = (begin + end) / 2;
        
        if(arr[mid] > target) {
            end = mid;
        }
        else {
            begin = mid;
        }
    }
    
    if(arr[begin] == target) {
        return begin;
    }
    else if(target > arr[begin]) {
        return end;
    }
    else /* target < arr[begin] */ {
        return begin;
    }
}

void insertion_binary(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++) {
        int new_position = binary_search(arr, begin, i, arr[i]);
        
        int temp = arr[i];
        for(int j = i; j > new_position; j--) {
            arr[j] = arr[j - 1];
        }
        arr[new_position] = temp;
    }
}

void shell(int *arr, int begin, int end)
{
    // 3x+1 increment sequence:  1, 4, 13, 40, 121, 364, 1093, ...
    int h = 1;
    while(h < end/3) h = 3 * h + 1;
    
    while(h >= 1) {
        for(int i = h; i < end; i++) {
            for(int j = i; j >= h && arr[j] < arr[j-h]; j -= h) {
                std::swap(arr[j], arr[j - h]);
            }
        }
        
        h /= 3;
    }
}

// Merge two sorted sub-arrays at [begin, mid) and [mid, end).
void merge_array(int *arr, int *aux, int begin, int mid, int end)
{
    memcpy(aux + begin, arr + begin, (end - begin) * sizeof(int));

    int i = begin, j = mid;
    
    for(int k = begin; k < end; k++) {
        if(i >= mid) {
            arr[k] = aux[j++];
        }
        else if(j >= end) {
            arr[k] = aux[i++];
        }
        else {
            if(aux[j] < aux[i]) {
                arr[k] = aux[j++];
            }
            else {
                arr[k] = aux[i++];
            }
        }
    }
}

// Merge sort main procedure
void merge_sort(int *arr, int *aux, int begin, int end)
{
    if (end - begin <= 1) return;
    
    int mid = begin + (end - begin) / 2;
    
    merge_sort(arr, aux, begin, mid);
    merge_sort(arr, aux, mid, end);
    merge_array(arr, aux, begin, mid, end);
}

void merge_sort(int *arr, int begin, int end)
{
    int *aux = new int[end - begin];
    
    merge_sort(arr, aux, begin, end);
    
    delete[] aux;
}
