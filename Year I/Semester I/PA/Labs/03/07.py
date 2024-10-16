def f(n):
    fs = "{} * {} = {}"
    L = [[fs.format(i, j, i * j) for j in range(1, n + 1)] for i in range(1, n + 1)]
    return L


n = int(input())
L = f(n)
print(L)
for i in range(n):
    for j in range(n):
        if j == n - 1:
            endl = '\n'
        else:
            endl = " | "
        print(L[i][j], end=endl)
