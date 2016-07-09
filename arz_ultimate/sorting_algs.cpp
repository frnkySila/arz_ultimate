//
//  sorting_algs.cpp
//  arz_ultimate
//
//  Created by Ilya Gulkov on 7/7/16.
//  Copyright (c) 2016 Ilya Gulkov. All rights reserved.
//

#include "sorting_algs.h"

#include <iostream>
using namespace std;


void bubble_classic(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++)
    {
        for(int j = begin; j < end - i; j++) {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
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
                swap(arr[j], arr[j+1]);
                
                already_sorted = false;
            }
        }
        
        if(already_sorted) break;
    }
}

void bubble_tier2(int *arr, int begin, int end)
{
    int last_swap;
    
    do
    {
        last_swap = 0;
        
        for(int j = begin; j < last_swap; j++) {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                
                last_swap = j;
            }
        }
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

int binary_search(int *arr, int begin, int end, int target)
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
        return -1;
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
