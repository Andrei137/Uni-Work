def anagrame(s, t):
    if len(s) != len(t):
        return False
    ap = [0 for x in range(52)]
    for i in s:
        if i >= 'a' and i <= 'z':
            ap[ord(i) - ord('a')] += 1
        else:
            ap[ord(i) - ord('A') + 26] += 1
    for i in t:
        if i >= 'a' and i <= 'z':
            ap[ord(i) - ord('a')] -= 1
        else:
            ap[ord(i) - ord('A') + 26] -= 1
    for i in s:
        if ap[ord(i) - ord("a")] != 0:
            return False
    return True


def permutare(t, s):
    aux, p, k = t, {}, 1
    for i in s:
        p[k] = {aux.find(i) + 1}
        aux = aux.replace(i, " ", 1)
        k += 1
    return p


s, t = map(str, input().split())
if anagrame(s, t):
    p = permutare(s, t)
    q = permutare(t, s)
    print(p)
    print(q)
else:
    print("Nu sunt anagrame")
