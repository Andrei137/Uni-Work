def hanoi(n, a, b, c):
    if n == 1:
        print(a, "-->", b)
    else:
        hanoi(n - 1, a, c, b)
        print(a, "-->", b)
        hanoi(n - 1, c, b, a)


n = int(input())
hanoi(n, 'A', 'B', 'C')
