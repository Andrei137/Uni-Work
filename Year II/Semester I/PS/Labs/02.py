'''
se pot repeta?
da -> n ** k
nu -> conteaza ordinea?
      da -> A_k_n
      nu -> C_k_n

C_k_n = (k + 1) * (k + 2) * ... * (n - 1) * n / 1 * 2 * ... * (n - k)
      = (n - k + 1) * (n - k + 2) * ... * (n - 1) * n / 1 * 2 * ... * k
'''


def factorial(n):
    if n == 0:
        return 1
    return factorial(n - 1) * n


def aranjamente(n, k):
    return factorial(n) / factorial(n - k)


def combinari(n, k):
    return factorial(n) / (factorial(k) * factorial(n - k))


def parole(n, k):
    return n ** k


def ex_1_aux(nr_caractere):
    nr_parole = parole(nr_caractere, 8)
    print("Numarul de parole pe care le putem introduce este {}".format(nr_parole))
    print("Timpul necesar pentru a testa toate parolele este {}".format(nr_parole / 1000000))
    nr_incercari = 7 * 24 * 60 * 60 * 1000000
    prob_spart = nr_incercari / nr_parole
    print("Probabilitatea de a sparge parola este {}".format(prob_spart))


def ex_1():
    ex_1_aux(62)
    ex_1_aux(36)


def ex_2():
    nr_moduri = factorial(15) // factorial(5)
    print("Numarul de moduri in care putem aseza studentii este {}".format(nr_moduri))


def ex_3():
    nr_moduri = factorial(10) // (factorial(3) * factorial(7))
    print("Numarul de moduri in care putem aseza studentii este {}".format(nr_moduri))


def ex_4_aux(calc_stricate):
    return combinari(13, 6 - calc_stricate) * combinari(7, calc_stricate) / combinari(20, 6)


def ex_4():
    print("Probabilitatea este {}".format(ex_4_aux(3)))
    nr_maxim = max([[ex_4_aux(i), i] for i in range(7)])
    print("Numarul cel mai probabil de laptopuri este: {}".format(nr_maxim[1]))


def ex_5_aux(asi):
    return combinari(48, 5 - asi) * combinari(4, asi) / combinari(52, 5)


def ex_5():
    print("Probabilitatea este {}".format(ex_5_aux(3)))
    nr_maxim = max([[ex_5_aux(i), i] for i in range(5)])
    print("Numarul cel mai probabil de asi este: {}".format(nr_maxim[1]))


c = int(input("Introduceti numarul problemei: "))
if c == 1:
    ex_1()
elif c == 2:
    ex_2()
elif c == 3:
    ex_3()
elif c == 4:
    ex_4()
elif c == 5:
    ex_5()
