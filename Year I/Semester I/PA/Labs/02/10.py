def encrypt(x, k):
    if x.isalpha():
        c = ord('a') if x >= 'a' and x <= 'z' else ord('A')
        x = chr((ord(x) - c + k) % 26 + c)
    return x


def decrypt(x, k):
    return encrypt(x, 26 - k)


def f(c, s, k):
    t = ""
    if c == 'a':
        for x in range(len(s)):
            t = t + encrypt(s[x], k)
    elif c == 'b':
        for x in range(len(s)):
            t = t + decrypt(s[x], k)
    else:
        pass
    return t


k, s, c = int(input()), input(), input()
print(f(c, s, k))
