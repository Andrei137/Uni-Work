'''
arr = [int(x) for x in input().split()]
arrXor = 0
for i in range(0, len(arr)):
    for j in range(0, 2 ** (len(arr) - 1)):
        arrXor ^= arr[i]
print(arrXor)
'''

arr = [int(x) for x in input().split()]
print(1 - int(len(arr) > 1))
