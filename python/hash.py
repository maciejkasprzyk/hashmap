from collections import defaultdict
import matplotlib.pyplot as plt
import numpy as np

N = 100


with open("alfabet.txt") as file:
    alphabet = file.readline().split()[0]

# for c in alphabet:
#     print(c)
print(ord('ę'))
print([ord(c) for c in alphabet])



# codes = {}
# for i in range(len(alphabet)):
#     codes[alphabet[i]] = i

# print(codes)


# def plot_bar_x(x,y):
#     # this is for plotting purpose
#     index = np.arange(x)
#     plt.bar(index, y)
#     plt.savefig('wykres.png')

# def my_hash(s):
#     result = 0
#     for c in s:
#         result *= 31
#         result += codes[c]
#     return result % N


# with open("slowa.txt", encoding='utf-8') as file:
#     data = file.readline().split()
#     print(data)
#     print(len(data))

# hashes = defaultdict(int)
# for word in data:
#     hashes[my_hash(word)] += 1
#     # hashes[hash(word) % N] += 1

# print(hashes)


# y = [hashes[i]  for i in range(N)]

# print(y)

# plot_bar_x(N, y)

