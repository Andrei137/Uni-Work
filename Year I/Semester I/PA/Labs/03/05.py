def format(s):
    for ch in ".,?!":
        s = s.replace(ch, "")
    return s


fin = open("Txt Files/05.txt", "r")
s = format(fin.read())
fin.close()
t = set(input())
ok = False
for ch in s.split():
    if set(ch) == t:
        print(ch, end=' ')
        ok = True
if not ok:
    print("Nu exista")
