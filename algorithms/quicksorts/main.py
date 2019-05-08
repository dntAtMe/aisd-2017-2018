from __future__ import print_function
from __future__ import division
import sys
import random
import math
import numpy


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def insertion_sort(array, comparisons=0):
    for i in range(1, len(array)):
        j = i-1 
        key = array[i]
        while (array[j] > key) and (j >= 0):
           comparisons += 2
           array[j+1] = array[j]
           j -= 1
        array[j+1] = key
    return comparisons

def generate_permutation_array(array, n):
    for i in range(0, n):
        array.append(i+1)
    random.shuffle(array)    

def generate_random_array(array, n):
    for i in range(0, n):
        array.append(random.randint(-10000, 10000)) 

def partition(array, pivot=0):
    eprint()
    eprint("--------ENTERING PARTITION--------")
    comparisons = 0
    swaps = 0
    i = 0
    comparisons += 1
    eprint("COMPARISON (pivot_idx != 0): ", pivot, "!=", 0)
    if pivot !=0: 
        swaps += 1
        eprint("SWAP (array[0] with array[pivot]): ", array[0], "with", array[pivot])
        array[0],array[pivot] = array[pivot],array[0]

    for j in range(len(array)-1):
        comparisons += 1
        eprint("COMPARISON (array[j] < pivot): ", array[j+1], "<", array[0] )
        if array[j+1] < array[0]:
            swaps += 1
            eprint("SWAP (array[j] with array[i]): ", array[j+1], "with", array[i+1])
            array[j+1],array[i+1] = array[i+1],array[j+1]
            i += 1
    swaps += 1
    eprint("SWAP (array[i] with pivot): ", array[i], "with", array[0])            
    array[0],array[i] = array[i],array[0]
    eprint("--------LEAVING PARTITION--------")
    return i, comparisons, swaps

def random_select(array, i, comparisons = 0, swaps = 0):
    eprint()
    eprint("--------ENTERING RANDOMSELECT--------")
    
    comparisons += 1
    #if (len(array) == 1):
    #   return array[0], comparisons, swaps
    if len(array) <= 5:
        array.sort()
        #comparisons += insertion_sort(array)
        return array[i-1], comparisons, swaps


    partition_result = partition(array, random.randrange(len(array))) 
    mid = partition_result[0]
    comparisons += partition_result[1]
    swaps += partition_result[2]

    k = mid + 1

    comparisons += 1
    eprint("COMPARISON (i == k): ", i, "==", k)
    if (k == i):
        return array[mid], comparisons, swaps
    
    comparisons += 1
    eprint("COMPARISON (i < k): ", i, "<", k)
    if (i < k):
        return random_select(array[:mid], i, comparisons, swaps)
    
    return random_select(array[mid+1:], i - k, comparisons, swaps)

def select(array, i, comparisons=0, swaps=0):
    eprint()
    eprint("--------ENTERING SELECT--------")
    eprint("array: ", array)
    
    sublists = []
    subsize = 5
    
    if len(array) <= subsize:
        array.sort()
        #comparisons += insertion_sort(array)
        return array[i-1], comparisons, swaps

    no_medians = len(array) // subsize
    if len(array) % subsize != 0:
        no_medians += 1
    
    for j in range(no_medians):
        sublists.append(array[j * subsize : (j+1) * subsize])
    medians = []
    for sublist in sublists:
        sublist.sort()
        medians.append(sublist[len(sublist) // 2])

    result = select(medians, (no_medians + 1)// 2, 0, 0) 
    x = result[0]
    comparisons += result[1]
    swaps += result[2]
    eprint("median of medians: ", x )
    
    partition_result = partition(array, array.index(x))
    mid = partition_result[0]
    comparisons += partition_result[1]
    swaps += partition_result[2]
    #### Temporary
    #
    #array_lt = []
    #array_gt = []
    #for item in array:
    #    if item < x:
    #        array_lt.append(item)
    #    elif item > x:
    #        array_gt.append(item)
    #
    #
    #TODO: mid, partition function
    
    #k = len(array_lt) + 1
    k = mid + 1
    eprint("k: ", k)

    eprint("COMPARISON (i == k): ", i, "==", k)
    if i == k:
        return x, comparisons, swaps
    eprint("COMPARISON (i < k): ", i, "<", k)
    if i < k:
        return select(array[:mid], i, comparisons, swaps)
    return select(array[mid+1:], i-k, comparisons, swaps)

if __name__ == "__main__":
    if (len(sys.argv) < 2): 
        print("usage: ./main -r|-p")
        exit(1)

    random_array = sys.argv[1] == "-r"

    n = int(input())
    k = int(input())
    assert (1 <= k <= n)

    array = []

    if (random_array):
        generate_random_array(array, n)
    else:
        generate_permutation_array(array, n)

    total_comparisons = 0
    total_swaps = 0
    no_tries = 100
    results = []
    for i in range(no_tries):
        result = random_select(array[:], k)
        eprint("RANDOMSELECT #COMPARISONS: ", result[1])
        eprint("RANDOMSELECT #SWAPS: ", result[2])
       # for val in array:
       #     if val == result[0]:
       #         print("[", val, "]", end=' ')
       #     else:
       #         print(val, end=' ')
       # print()
        total_comparisons += result[1]
        total_swaps += result[2]
        results.append(result[1])
    print("RS: AVG #COMPARISONS: ", total_comparisons / no_tries)
    print("RS: AVG #SWAPS: ", total_swaps / no_tries)
    print("RS: MIN #COMP: ", min(results))
    print("RS: MAX #COMP: ", max(results))
    print("RS: VARIANCE: ", numpy.var(results))
    eprint("------------------------------------------------")
    
    results = []
    total_comparisons = 0
    total_swaps = 0
    for i in range(no_tries):
        result = select(array[:], k)
        eprint("SELECT #COMPARISONS: ", result[1])
        eprint("SELECT #SWAPS", result[2])
       # for val in array:
       #     if val == result[0]:
       #         print("[", val, "]", end=' ')
       #     else:
       #         print(val, end=' ')
       # print()
        total_comparisons += result[1]
        total_swaps += result[2]
        results.append(result[1])
    print("S: AVG #COMPARISONS: ", total_comparisons / no_tries)
    print("S: AVG #SWAPS: ", total_swaps / no_tries)
    print("S: MIN #COMP: ", min(results))
    print("S: MAX #COMP: ", max(results))
    print("S: VARIANCE: ", numpy.var(results))
    #pomiary