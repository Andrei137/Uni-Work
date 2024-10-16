def afisare(L):
    ncmax = max([len(str(max(x))) for x in L])
    for i in L:
        for j in i:
            print(str(j).rjust(ncmax), end=' ')
        print()


def createMatrix(n):
    L = [[0] * n for _ in range(n)]
    for i in range(n):
        L[i][n - 1] = L[n - 1][i] = 1
    for i in range(n - 2, -1, -1):
        for j in range(n - 2, -1, -1):
            L[i][j] = L[i + 1][j] + L[i][j + 1]
    afisare(L)


createMatrix(int(input()))
