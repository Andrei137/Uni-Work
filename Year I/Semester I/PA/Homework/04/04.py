def nrStr(s, n):
    rez = []
    for i in s:
        if len(i) == n:
            rez.append(i)
    return rez


s = [str(x) for x in input().split()]
n = int(input())
rez = nrStr(s, n)
for i in rez:
    print(i, end=" ")
