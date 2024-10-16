s, t = input().split()
s, t = [x for x in s], [x for x in t]
s, t = sorted(s), sorted(t)
if s == t:
    print("Sunt anagrame")
else:
    print("Nu sunt anagrame")
