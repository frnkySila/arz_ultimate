//
//  sorting_debug.h
//  arz_ultimate
//
//  Created by Ilya Gulkov on 11/7/16.
//  Copyright (c) 2016 Ilya Gulkov. All rights reserved.
//

#ifndef __arz_ultimate__sorting_debug__
#define __arz_ultimate__sorting_debug__

enum sort_mode { random_array, random_array_small, completely_sorted, nearly_sorted, reversed, few_unique };

int *create_array(int size, sort_mode mode);
int *create_sizes_linear(int num_sizes, int min, int max);
bool is_sorted(int *arr, int begin, int end);
bool same_elements(int *arr1, int begin1, int *arr2, int begin2, int length);

#endif /* defined(__arz_ultimate__sorting_debug__) */
