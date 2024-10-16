x, y = map(int, input().split())
x ^= y
y ^= x
x ^= y
print(x, y)
