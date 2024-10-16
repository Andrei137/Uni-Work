def gen_primes():
    yield 2
    x = 3
    while True:
        d = 3
        while d * d <= x and x % d:
            d += 2
        if d * d > x:
            yield x
        x += 2


c, n = input().split()
n = int(n)
count = 0
for x in gen_primes():
    if x > n and c == 'a':
        break
    elif count == n and c == 'b':
        break
    print(x, end=" ")
    count += 1
