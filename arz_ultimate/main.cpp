//
//  Created by Ilya Gulkov on 5/7/16 in XCode 6.4 on MacBook Pro Retina 2013 kuplennom za 90k pri starom dalare
//

#include "sorting_algs.h"

#include <iostream>
#include <cstdlib>
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

bool is_sorted(int *arr, int begin, int end)
{
    for(int i = 0; i < end - 1; i++) {
        if(arr[i] > arr[i+1]) {
            return false;
        }
    }
    
    return true;
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

void unit_test_sorting(sort_function f_sort)
{
    int *arr;
    
    arr = create_array(10000, random_array);
    
    f_sort(arr, 0, 10000);
    
    if(!is_sorted(arr, 0, 10000)) {
        throw 1337;
    }
    
    delete[] arr;
    
    arr = create_array(10000, nearly_sorted);
    
    f_sort(arr, 0, 10000);
    
    if(!is_sorted(arr, 0, 10000)) {
        throw 1337;
    }
    
    delete[] arr;
    
    arr = create_array(10000, reversed);
    
    f_sort(arr, 0, 10000);
    
    if(!is_sorted(arr, 0, 10000)) {
        throw 1337;
    }
    
    delete[] arr;
    
    arr = create_array(10000, few_unique);
    
    f_sort(arr, 0, 10000);
    
    if(!is_sorted(arr, 0, 10000)) {
        throw 1337;
    }
    
    delete[] arr;
}

void bubble_classic(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++)
    {
        outer_cycles += 1;
        
        for(int j = begin; j < end - i; j++) {
            inner_cycles += 1;
            
            if(arr[j] > arr[j+1])
            {
                swaps += 1;
                
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void bubble_tier1(int *arr, int begin, int end)
{
    for(int i = begin + 1; i < end; i++)
    {
        outer_cycles += 1;
        
        bool already_sorted = true;
        
        for(int j = begin; j < end - i; j++) {
            inner_cycles += 1;
            
            if(arr[j] > arr[j+1])
            {
                swaps += 1;
                
                swap(arr[j], arr[j+1]);
                
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
        outer_cycles += 1;
        
        int new_last_swap = 0;
        
        for(int j = begin; j < last_swap; j++) {
            inner_cycles += 1;
            
            if(arr[j] > arr[j+1])
            {
                swaps += 1;
                
                swap(arr[j], arr[j+1]);
                
                new_last_swap = j;
            }
        }
        
        last_swap = new_last_swap;
    } while(last_swap != 0);
}

void insertion(int *arr, int begin, int end)
{
    comparisons += 1;
    for(int i = begin + 1; i < end; i++) {
        
        // Possible optimization: replace swaps with assignments
        for(int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            comparisons += 1;
            swaps += 1;
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
int binary_search(int *arr, int begin, int end, int target)
{
    while(begin - end < -1) {
        int mid = (begin + end) / 2;
        
        comparisons += 1;
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
    comparisons += 1;
    for(int i = begin + 1; i < end; i++) {
        int new_position = binary_search(arr, begin, i, arr[i]);
        
        int temp = arr[i];
        for(int j = new_position; j < i; j++) {
            swaps += 1;
            arr[j + 1] = arr[j];
        }
        swaps += 1;
        arr[new_position] = temp;
    }
}

void test_algorithm_bubble(int *arr, int task_size, string name, sort_function f_sort)
{
    int *newArr = new int[task_size];
    memcpy(newArr, arr, task_size * sizeof(int));
    
    outer_cycles = inner_cycles = swaps = 0;
    f_sort(newArr, 0, task_size);
    cout << name << '\t' << outer_cycles << '\t' << inner_cycles << '\t' << swaps << endl;
    
    //    print_array(newArr, 0, task_size);
    //    cout << is_sorted(newArr, 0, task_size) << endl;
    
    delete[] newArr;
}

void test_algorithm_insertion(int *arr, int task_size, string name, sort_function f_sort)
{
    int *newArr = new int[task_size];
    memcpy(newArr, arr, task_size * sizeof(int));
    
    comparisons = swaps = 0;
    f_sort(newArr, 0, task_size);
    cout << name << '\t' << comparisons << '\t' << swaps << endl;
    
    //    print_array(newArr, 0, task_size);
    //    cout << is_sorted(newArr, 0, task_size) << endl;
    
    delete[] newArr;
}

int main(int argc, const char * argv[]) {
    unsigned int task_size;
    cout << "Введите размер задачи: ";
    cin >> task_size;
    
    char c;
    cout << "Выберите тип массива (m - ручной ввод, r - случайный, n - почти отсортированный, v - отсортированный в обратном порядке, f - мало разных значений): ";
    cin >> c;
    
    sort_mode mode;
    switch (c) {
        case 'm':
            mode = manual_entry;
            break;
        case 'r':
            mode = random_array;
            break;
        case 'n':
            mode = nearly_sorted;
            break;
        case 'v':
            mode = reversed;
            break;
        case 'f':
            mode = few_unique;
            break;
        default:
            cout << "Чет не то";
            return 0;
    }
    
    int *arr = create_array(task_size, mode);
    
    //    cout << '\t' << "Внешние ц." << '\t' << "Внутренние ц." << '\t' << "Перестановки" << endl;
    //    test_algorithm_bubble(arr, task_size, "Обычный   ", &bubble_classic);
    //    test_algorithm_bubble(arr, task_size, "Айверсон 1", &bubble_tier1);
    //    test_algorithm_bubble(arr, task_size, "Айверсон 2", &bubble_tier2);
    
    cout << '\t' << "Сравнения" << '\t' << "Обмены" << endl;
    test_algorithm_insertion(arr, task_size, "Вставки        ", &insertion);
    test_algorithm_insertion(arr, task_size, "Вставки (бин.) ", &insertion_binary);
    
    delete[] arr;
    
    return 0;
}
