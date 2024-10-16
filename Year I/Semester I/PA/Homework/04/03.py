cerinta = input()

T = [("Capra cu trei iezi", ["Ion Creanga"], 1875, 12),
     ("Endgame: The Calling", ["James Frey", "Nils Johnson-Shelton"], 2014, 50),
     ("616. Totul este infern", ["David Zurdo", "Angel Gutierrez"], 2008, 43),
     ("Alchimistul", ["Paulo Coelho", "Alan R Clarke", "James Noel Smith"], 2014, 38),
     ("Ciresarii Vol 1", ["Constantin Chirita"], 1956, 14),
     ("Winnetou Vol 1", ["Karl May", "Pandu Ganesa"], 1893, 25),
     ("Povestea lui Harap-Alb", ["Ion Creanga"], 1877, 16)]

if cerinta == "a":
    def ieftinire(T):
        for i in range(len(T)):
            titlu, autori, an, pret = T[i]
            if an < 2000:
                pret -= 0.2 * pret
            T[i] = titlu, autori, an, pret

    ieftinire(T)
    print(*T, sep="\n")
else:
    def criteriu_1(T):
        return -T[2], T[0]

    def criteriu_2(T):
        return -len(T[1]), \
               -T[3]

    def criteriu_3(T):
        return " ".join(T[1]).split()[1], " ".join(T[1]).split()[0], T[0], T[2]

    criteriu = int(input())

    if criteriu == 1:
        T.sort(key=criteriu_1)
    elif criteriu == 2:
        T.sort(key=criteriu_2)
    else:
        T.sort(key=criteriu_3)

    print(*T, sep="\n")
