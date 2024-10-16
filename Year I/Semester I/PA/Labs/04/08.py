fin = open("Txt Files/08.txt", "r")
s = fin.read().split()
fin.close()
d = {x[-2:]: set([y for y in s if x[-2:] == y[-2:]]) for x in s}
fout = open("Txt Files/rime.txt", "w")
for x in d.items():
    if len(x[1]) >= 2:
        fout.write(x[0] + " : [" + ", ".join(sorted(x[1])) + "]\n")
fout.close()
