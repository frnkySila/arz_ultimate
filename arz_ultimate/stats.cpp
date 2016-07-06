//
//  stats.cpp
//  arz_ultimate
//
//  Created by Ilya Gulkov on 7/7/16.
//  Copyright (c) 2016 Ilya Gulkov. All rights reserved.
//

#include "stats.h"

#include <iostream>
using namespace std;

long long array_max(long long *arr, int size)
{
    long long max = LLONG_MIN;
    
    for(int i = 0; i < size; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    
    return max;
}

long long array_min(long long *arr, int size)
{
    long long min = LLONG_MAX;
    
    for(int i = 0; i < size; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    
    return min;
}

long long array_avg(long long *arr, int size)
{
    // Computing in double creates the possiblity of precision loss, but diminishes one of overflow
    double avg = 0.0;
    
    for(int i = 0; i < size; i++) {
        avg += arr[i] / (double)size;
    }
    
    return (long long)avg;
}
