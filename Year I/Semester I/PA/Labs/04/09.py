def f_k(k):
    def F(x):
        return x < k
    return F


f_100 = f_k(100)
print(f_k(5)(3), f_100(3), f_100(101))


L = [int(x) for x in input().split()]
is_sorted = False
while not is_sorted:
    is_sorted = True
    for i in range(len(L) - 1):
        f_i = f_k(L[i])
        for j in range(i + 1, len(L)):
            if f_i(L[j]):
                L[i], L[j] = L[j], L[i]
                is_sorted = False
print(*L)
