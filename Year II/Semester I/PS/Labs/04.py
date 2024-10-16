import numpy as np
import datetime as dt


def zar1(s):
    if (s == "verde"):
        return [3, 3, 3, 3, 3, 6]
    if (s == "rosu"):
        return [2, 2, 2, 5, 5, 5]
    if (s == "negru"):
        return [1, 4, 4, 4, 4, 4]


def zar_rosu():
    return np.array([2, 2, 2, 5, 5, 5])[(np.random().random(10**8) * 6).astype(int)]


def zar_verde():
    return np.array([3, 3, 3, 3, 3, 6])[(np.random().random(10**8) * 6).astype(int)]


def zar_negru():
    return np.array([1, 4, 4, 4, 4, 4])[(np.random().random(10**8) * 6).astype(int)]


def zar2(s):
    if (s == "verde"):
        return zar_verde()
    if (s == "rosu"):
        return zar_rosu()
    if (s == "negru"):
        return zar_negru()


def sim1(str1, str2):
    arr1 = zar1(str1)
    arr2 = zar1(str2)

    wins1 = 0
    wins2 = 0
    for i in range(10**6):
        if (np.random.choice(arr1) > np.random.choice(arr2)):
            wins1 += 1
        if (np.random.choice(arr1) < np.random.choice(arr2)):
            wins2 += 1
    print(f"Probabilitatea ca {str1} sa castige vs {str2} este { wins1 / (wins1 + wins2) }")


def sim2(str1, str2):
    arr1 = zar2(str1)
    arr2 = zar2(str2)


start = dt.datetime.now()
print(start)
sim1("verde", "rosu")
sim1("verde", "negru")
sim1("rosu", "negru")
print(dt.datetime.now() - start)
