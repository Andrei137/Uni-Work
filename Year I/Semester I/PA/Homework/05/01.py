import random as rnd
from datetime import datetime
rnd.seed(datetime.now().timestamp())


def afisareMatrice(L):
    ncmax = max([len(str(max(x))) for x in L])
    for i in L:
        for j in i:
            print(str(j).rjust(ncmax), end=' ')
        print()


# Subpunctul a) - Generare matrice dublu sortata
def generateMatrix(m, n):
    upperLimit = 100
    matrix = [[_] * n for _ in range(m)]
    matrix[0][0] = rnd.randint(0, upperLimit - n * m) 

    # Initializarea primei linii cu un vector sortat strict crescator
    for i in range(1, n):
        matrix[0][i] = rnd.randint(matrix[0][i - 1] + 1, upperLimit - n * m + i)

    # Initializarea restul elementelor cu valori strict mai mari decat cea de sus si cea din stanga
    for i in range(1, m):
        matrix[i][0] = rnd.randint(matrix[i - 1][0] + 1, upperLimit - n * m + i)
        for j in range(1, n):
            lowerLimit = max(matrix[i - 1][j], matrix[i][j - 1])
            matrix[i][j] = rnd.randint(lowerLimit + 1, upperLimit - n * m + i * j + 1)

    afisareMatrice(matrix)
    return matrix


# Subpunctul b)
# O(m * n) - Cautare element cu element
def cautare1(L, x):
    for i in range(len(L)):
        for j in range(len(L[i])):
            if L[i][j] == x:
                return i, j
    return None


# O(m * log(n)) - Cautare binara pe linii
def cautare2(L, x):
    for i in range(len(L)):
        left = 0
        right = len(L[i]) - 1
        while left <= right:
            middle = (left + right) // 2
            if L[i][middle] == x:
                return i, middle
            elif L[i][middle] > x:
                right = middle - 1
            else:
                left = middle + 1
    return None


# O(m + n) - Cautare din coltul dreapta sus
def cautare3(L, x):
    i = 0
    j = len(L[i]) - 1
    while i < len(L) and j >= 0:
        if L[i][j] == x:
            return i, j
        elif L[i][j] > x:
            j -= 1
        else:
            i += 1
    return None


m, n, x = map(int, input().split())
L = generateMatrix(m, n)
print(cautare1(L, x))
print(cautare2(L, x))
print(cautare3(L, x))
