L = [int(x) for x in input().split()]
print([(L[i], L[i + 1]) for i in range(len(L) - 1)])
