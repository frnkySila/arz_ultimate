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


inline void bubble_classic(int *arr, int begin, int end)
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

inline void bubble_tier1(int *arr, int begin, int end)
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

inline void bubble_tier2(int *arr, int begin, int end)
{
    int last_swap = end - 1;
    
    do
    {
        int new_last_swap = 0;
        
        for(int j = begin; j < last_swap; j++) {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                
                new_last_swap = j;
            }
        }
        
        last_swap = new_last_swap;
    } while(last_swap != 0);
}

inline void insertion(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++) {
        
        // Possible optimization: replace swaps with assignments
        for(int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(arr[j - 1], arr[j]);
        }
    }
}

/*
 // Функция бинарного поиска
 //
 // Поиск выполняется среди элементов с индексами на промежутке [begin, end) отсортированного массива
 // Возвращает индекс последнего вхождения элемента, равного target
 // Если элемента в массиве нет, то возвращает индекс, куда его можно было бы вставить, не нарушая отсортированности массива
 // Если элемент больше наибольшего в массиве — end, если меньше наименьшего — -1
 */
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
        return -1;
    }
}

inline void insertion_binary(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++) {
        int new_position = binary_search(arr, begin, i, arr[i]);
        
        int temp = arr[i];
        for(int j = new_position; j < i; j++) {
            arr[j + 1] = arr[j];
        }
        arr[new_position] = temp;
    }
}
