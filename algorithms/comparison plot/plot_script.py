import sys
import numpy as np
import matplotlib.pyplot as plt

def fill_array(tmp, index):
    #prev_x = int(array[0][0] / 100)
    prev_x = 0
    counter = 1 
    for x in range(len(array)):
        current_x = int(array[x][0] / 100)
        if (prev_x < current_x):
            tmp.extend([array[x][index]])
            #print(counter)
            tmp[prev_x] /= counter
            #print(tmp)
            #print(current_x, len(tmp)-1)
            counter = 1
            prev_x = current_x
        else:
            counter += 1
            tmp[prev_x] += array[x][index]
    tmp[prev_x] /= counter 

filenames = sys.argv[1:]
comparisons = [0]
swaps = [0]
times = [0]
y1 = []
y2 = []
y3 = []
y4 = []

rows = 2
cols = 3

colors = ['b-', 'g-', 'r-', 'y-']

for filename in filenames:
    print(filename)
    with open(filename) as f:
        array = [[float(x) for x in line.split()] for line in f]
        comparisons = [0]
        swaps = [0]
        times = [0]

        fill_array(comparisons, 1)
        fill_array(swaps, 2)
        fill_array(times, 3)

    color = colors.pop(0)
    
    y1 = comparisons
    y2 = swaps
    y3 = times
    y4 = [0 if i == 0 else (comparisons[i] / (i * 100)) for i in range(len(comparisons))]

    x = np.linspace(0, (len(comparisons) - 1) * 100, len(comparisons))

    plt.subplot(rows, cols, 1)
    plt.plot(x, y1, color)
    
    plt.subplot(rows, cols, 2)
    plt.plot(x, y2, color)
    
    plt.subplot(rows,cols, 3)
    plt.plot(x, y3, color)

    plt.subplot(rows, cols, 4)
    plt.plot(x, y4, color)

plt.subplot(rows, cols, 1)
plt.title('# of comparisons')


plt.subplot(rows, cols, 2)
plt.title('# of swaps')
plt.xlabel('n')

plt.subplot(rows, cols, 3)
plt.title('execution time')
plt.xlabel('n')

plt.subplot(rows, cols, 4)
plt.title('# of comparisons / n')

plt.show()
