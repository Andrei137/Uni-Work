import math
x = int(input())
k = 1 + math.floor(math.log2(x))
y = x ^ ((1 << k) - 1)
count = 0
while y:
    count += 1
    y &= y - 1
print(count)
