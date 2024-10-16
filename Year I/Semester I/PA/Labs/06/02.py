stk = []


def bkt(s):
    if s == 0:
        print(*stk)
        return
    for i in range(stk[-1] + 1 if len(stk) else 1, s + 1):
        stk.append(i)
        bkt(s - i)
        stk.pop()


bkt(int(input()))
