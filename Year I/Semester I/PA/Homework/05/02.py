def cheieProfit(p):
    return p[2]


fin = open("Txt Files/proiecte.in")
lp = []
for linie in fin:
    aux = linie.split()
    lp.append((aux[0], int(aux[1]), float(aux[2])))
fin.close()

lp.sort(key=cheieProfit, reverse=True)
zi_max = max([p[1] for p in lp])
planificare = {k: None for k in range(1, zi_max + 1)}
profit = 0

for proiect in lp:
    for z in range(proiect[1], 0, -1):
        if planificare[z] is None:
            planificare[z] = proiect
            profit += proiect[2]
            break

# Count tine minte numarul de zile libere si le scade din indexul zilei lucratoare
# In exemplul dat, ziua 4 este libera, astfel count devine 1, iar ziua 5 devine ziua 4 la afisare
# In rest, sintaxa ramane aceeasi cu cea de la problema 5 din seminar
count = 0
fout = open("Txt Files/proiecte.out", "w")
for z in planificare:
    if planificare[z] is not None:
        fout.write(f"Ziua {z - count}: {planificare[z][0]}  {planificare[z][2]}\n")
    else:
        count += 1
fout.write("\nProfit maxim: " + str(profit))
fout.close()
