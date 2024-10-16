def ex14(L):
    L = L.lower()
    d1 = {x: L.count(x) for x in L.split()}
    d2 = {x: [y[0] for y in d1.items() if y[1] == x] for x in d1.values()}

    return max(d2.items())[1]


L = input()
print(ex14(L))
