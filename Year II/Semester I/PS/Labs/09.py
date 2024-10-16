import numpy as np


def P_Ank(n, k):
    s = 0
    for i in range(k, n):
        s += 1 / i
    return s * (k / n)


def ex_2():
    for n in range(3, 10000):
        maxx = 0
        for k in range(1, n):
            if P_Ank(n, k) > maxx:
                maxx = P_Ank(n, k)
        print(f"Pentru n = {n} valoarea maxima este {maxx}")


ex_2()
