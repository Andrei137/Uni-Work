x, y = map(int, input().split())
z = x ^ y
count = 0
while z:
    count += 1
    z &= z - 1
print(count)
