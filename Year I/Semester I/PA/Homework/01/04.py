'''
n = int(input("n = "))
if not n:
    print("Invalid")
elif not(n & (n - 1)):
    print(n)
else:
    count = 0
    while n:
        n >>= 1
        count += 1
    print(1 << (count - 1))
'''

import math
n = int(input())
k = math.floor(math.log2(n))
print((1 << k) if n > 1 else "Invalid")
