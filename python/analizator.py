import sys
import subprocess
import pathlib
import os
from random import randrange

import matplotlib.pyplot as plt
import numpy as np
from tabulate import tabulate

# argv
# 1 txt file with words
# 2 folder to save results
# 3 size of array used in hashtable
# 4 max tested size
if __name__ == '__main__':
    try:
        words_file = os.path.abspath(sys.argv[1])
        results_directory = os.path.abspath(sys.argv[2])
        n = int(sys.argv[3])
        k = sys.argv[4]

        # directory of where script is located
        python_path = os.path.dirname(os.path.abspath(__file__))
        main_path = pathlib.Path(python_path).parent / 'hashmap' / 'bin' / 'hashmap.exe'
        print(main_path)
    except:
        print('Usage: analizator.py words.txt results_directory size_of_array max_size')
        exit(-1)
    if n <= 100:
        print('Size of array must be bigger than 100.')
        exit(-1)

    results = []

    for n in np.arange(n // 100, n + 1, n // 100):
        avg = [0, 0, 0]
        for _ in range(5):
            child = subprocess.run([str(main_path), words_file, str(n), k, str(randrange(n-1))], stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE)
            print(n)
            if child.returncode != 0:
                print(child.stderr)
                exit(-1)
            out = child.stdout.decode('UTF-8').split()
            avg = [a + float(b) for a, b in zip(avg, out)]
        avg = [x / 5 for x in avg]
        results.append([n] + avg)

    x = [x[0] for x in results]
    remove = [x[1] for x in results]
    add = [x[2] for x in results]
    enu = [x[3] for x in results]

    fig, ax = plt.subplots()
    ax.set(xlabel='n - number of elements in collection', ylabel='time [ms]')
    ax.grid()
    ax.plot(x, remove)
    ax.set(title=f'Removing element from collection with n elements. Array size: {k}')
    fig.savefig(pathlib.Path(results_directory) / 'remove.png')

    fig, ax = plt.subplots()
    ax.set(xlabel='n - number of elements in collection', ylabel='time [ms]')
    ax.grid()
    ax.plot(x, add)
    ax.set(title=f'Adding element to collection with n elements. Array size: {k}')
    fig.savefig(pathlib.Path(results_directory) / 'add.png')

    fig, ax = plt.subplots()
    ax.set(xlabel='n - number of elements in collection', ylabel='time [ms]')
    ax.grid()
    ax.plot(x, enu)
    ax.set(title=f'Enumerating collection with n elements. Array size: {k}')
    fig.savefig(pathlib.Path(results_directory) / 'enumerate.png')

    with open(pathlib.Path(results_directory) / 'table.txt', '+w') as file:
        table = [[a, b] for a, b in zip(x, remove)][9::10]
        m_i = len(table) // 2 # median index
        t_median = table[m_i][1]
        table = [[n, t, t / t_median] for n, t in table]

        file.write("Remove\n")
        file.write(tabulate(table, headers=["n", "t(n)", "q(n)"]))

        table = [[a, b] for a, b in zip(x, add)][9::10]
        t_median = table[m_i][1]
        table = [[n, t, t / t_median] for n, t in table]

        file.write("\nAdd\n")
        file.write(tabulate(table, headers=["n", "t(n)", "q(n)"]))

        table = [[a, b] for a, b in zip(x, enu)][9::10]
        t_median = table[m_i][1]
        median = table[m_i][0]
        table = [[n, t, (t / n) * (median / t_median)] for n, t in table]

        file.write("\nEnumerate\n")
        file.write(tabulate(table, headers=["n", "t(n)", "q(n)"]))
