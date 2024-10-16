def f(x):
    if x in "aeiou":
        x += 'p' + x
    elif x in "AEIOU":
        x += 'p' + x.lower()
    return x


s = input()
print(''.join(map(f, s)))
