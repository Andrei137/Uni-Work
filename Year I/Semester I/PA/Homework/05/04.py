def afisarePozitive(x, power, first):
    if power:
        if first:
            print(f"{x} * x^{power}", end="")
        else:
            if x < 0:
                x = -x
                print(f" - {x} * x^{power}", end="")
            else:
                print(f" + {x} * x^{power}", end="")
    else:
        if x < 0:
            x = -x
            print(f" - {x}", end="")
        else:
            print(f" + {x}", end="")


def afisareNegative(x, power, first):
    if power:
        if first:
            print(f"{x} * x^{power}", end="")
        else:
            if x < 0:
                x = -x
                print(f" - {x} * x^{power}", end="")
            else:
                print(f" + {x} * x^{power}", end="")
    else:
        if x < 0:
            x = -x
            print(f" - {x}", end="")
        else:
            print(f" + {x}", end="")


A = [float(i) for i in input().split()]
x0 = float(input())
A.sort()
power = step = len(A) - 1

# Cazul I - X0 este nenegativ

# Cazul II.1 - Daca x0 apartine [1, inf), se aleg elementele din A descrescator
if x0 >= 1:
    for i in range(step, -1, -1):
        afisarePozitive(A[i], power, (i == step))
        power -= 1

# Cazul I.2 - Daca x0 apartine [0, 1), se aleg elementele din A crescator
elif x0 >= 0:
    for i in range(0, step + 1):
        afisarePozitive(A[i], power, (i == 0))
        power -= 1

# Cazul II - X0 este negativ
# Pentru acest caz, la puteri pare se alege maximul si la puteri impare se alege minimul
# Prioritatea puterilor o decide intervalul in care se afla x0

# Cazul II.1 - Daca x0 apartine (inf, -1], puterile au prioritate descrescatoare
# x^(len(A) - 1) va contine primul maxim / minim gasit, dupa paritate, apoi x^(len(A) - 2) s.a.m.d.
elif x0 <= -1:
    j, k = 0, step
    for i in range(step + 1):
        if power % 2:
            afisareNegative(A[j], power, (i == 0))
            j += 1
        else:
            afisareNegative(A[k], power, (i == 0))
            k -= 1
        power -= 1
# Cazul II.2 - Daca x0 apartine (-1, 0), puterile au prioritate crescatoare
# x^0 va contine primul maxim, apoi x^1 va contine primul minim, apoi x^2 al doilea maxim s.a.m.d.
else:
    j, k = (power - 1) // 2, (power + 1) // 2
    print(j, k)
    for i in range(step + 1):
        if power % 2:
            afisareNegative(A[j], power, (i == 0))
            j -= 1
        else:
            afisareNegative(A[k], power, (i == 0))
            k += 1
        power -= 1
