stk = []


def bkt(s):
    if s == 0:
        print(*stk)
        return
    for i in range(1, s + 1):
        stk.append(i)
        bkt(s - i)
        stk.pop()


bkt(int(input()))
