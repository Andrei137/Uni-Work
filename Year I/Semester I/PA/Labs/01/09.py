def cmmdc(n, m):
    while m:
        r = n % m
        n = m
        m = r
    return n


L1, L2 = map(int, input().split())
d = cmmdc(L1, L2)
print((L1 // d) * (L2 // d))
