def cheieKm(t):
    return t[0], -t[1]


fin = open("Txt Files/autostrada.in")
totalLen = int(fin.readline())
km = []
for linie in fin:
    aux = linie.split()
    km.append((int(aux[0]), int(aux[1])))
fin.close()

km.sort(key=cheieKm)
currMin = km[0][0]
currMax = km[0][1]
reunion = []
damagedLen = currMax - currMin

for i in range(1, len(km)):
    if km[i][1] <= currMax:
        continue
    elif km[i][0] < currMax:
        damagedLen += km[i][1] - currMax
        currMax = km[i][1]
    else:
        damagedLen += km[i][1] - km[i][0]
        reunion.append((currMin, currMax))
        currMin, currMax = km[i]

reunion.append((currMin, currMax))

# Subpunctul a) - Afisarea portiunilor avariate, in aceeasi maniera ca la problema 3 din seminar
fout = open("Txt Files/autostrada.out", "w")
for i in reunion:
    fout.write(f"[{i[0]}, {i[1]}]\n")

# Subpunctul b) - Afisarea portiunilor neavariate cu ajutorul celor avariate
# Reuniunea intervalelor ce apartin [0, totalLen] \ portiunile avariate
fout.write("\n")
if reunion[0][0] != 0:
    fout.write(f"(0, {reunion[0][0]})\n")
for i in range(len(reunion) - 1):
    fout.write(f"({reunion[i][1]}, {reunion[i + 1][0]})\n")
if reunion[-1][1] != totalLen:
    fout.write(f"({reunion[-1][1]}, {totalLen})\n")

# Supunctul c) - Afisarea gradului de uzura
fout.write(f"\n{int(damagedLen * 100 / totalLen)}%")
fout.close()
