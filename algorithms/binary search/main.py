
def binary_search(array, key, no_comparisons = 0):
    if len(array) == 0:
        return 0, no_comparisons
    mid = len(array) // 2
    
    if array[mid] == key:
        return 1, no_comparisons + 1
    
    if key < array[mid]:
        no_comparisons += 1
        return binary_search(array[:mid], key, no_comparisons)
    else:
        return binary_search(array[mid+1:], key, no_comparisons)

def benchmark_bs(array, key):
    start_time = timeit.default_timer()
    result_tuple = binary_search(array, key) 
    end_time = timeit.default_timer()
    
    print("array length: ", len(array))
    print("binary search result: ", result_tuple[0])
    print("execution time (ms): ", (end_time - start_time) * 1000)
    print("# comparisons: ", result_tuple[1])

if __name__=='__main__':
    import sys
    import random 
    import timeit
    from time import time

    array = []
    v = int(input())
    if(len(sys.argv) < 2):
        array = [int(num) for num in input().split(' ')]
        benchmark_bs(array, v)
    elif (sys.argv[1] == '--test'):
        for n in range(1000, 101000, 1000):
            for i in range(n-1000, n):
                array.append(i)
            benchmark_bs(array, v)
            benchmark_bs(array, n/4)                        

    
    

#array = []
#for i in range(n):
#    array.append(int(input()))
#time_start = time()
#time_end = time()

