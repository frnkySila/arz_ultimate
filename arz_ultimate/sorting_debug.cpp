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
using namespace std;

void print_array(int *arr, int begin, int end)
{
    for(int i = begin; i < end; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
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
    set<int> elems1{}, elems2{};
    
    for(int i = begin1; i < begin1 + length; i++) {
        elems1.insert(arr1[i]);
    }
    
    for(int i = begin2; i < begin2 + length; i++) {
        elems2.insert(arr2[i]);
    }
    
    return elems1 == elems2;
}
