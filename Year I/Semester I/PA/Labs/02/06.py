def f(s):
    return ' ' + s + ' '


prop = input()
s, t = input().split()
prop, s, t = f(prop), f(s), f(t)
prop = prop.replace(s, t)
prop = prop[1:len(prop) - 1]
print(prop)
