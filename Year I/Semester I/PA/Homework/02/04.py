def e(x, n):
    if x.isalpha():
        if x >= 'a' and x <= 'z':
            x = chr((ord(x) - ord('a') + n) % 26 + ord('a'))
        else:
            x = chr((ord(x) - ord('A') + n) % 26 + ord('A'))
    return x


def d(x, n):
    return e(x, 26 - n)


s, n, t = input(), int(input()), ""
for x in range(len(s)):
    t = t + e(s[x], n)
print(t)
s, n, t = input(), int(input()), ""
for x in range(len(s)):
    t = t + d(s[x], n)
print(t)
