from copy import deepcopy


def formatString(misionari, canibali, sep):
    return f"{misionari} misionar{'i' if misionari != 1 else ''}" + sep + \
           f"{canibali} canibal{'i' if canibali != 1 else ''}"


class Info:
    def __init__(self, canibali, misionari, pozitieBarca):
        self.canibali = canibali
        self.misionari = misionari
        self.pozitieBarca = pozitieBarca  # 0 - stang, 1 - drept

    def __eq__(self, other):
        return self.canibali == other.canibali and \
               self.misionari == other.misionari and \
               self.pozitieBarca == other.pozitieBarca

    def __str__(self):
        return formatString(self.misionari, self.canibali, ", ") + " | " + \
               formatString(Nod.N - self.misionari, Nod.N - self.canibali, ", ") + \
               f"\nBarca se afla pe malul {'stang' if self.pozitieBarca == 0 else 'drept'}"

    def __repr__(self):
        return f"({self.misionari}, {self.canibali}, {self.pozitieBarca})"

    def validState(self):
        if self.misionari != 0 and self.canibali > self.misionari:  # malul stang
            return False
        if self.misionari != Nod.N and Nod.N - self.canibali > Nod.N - self.misionari:  # malul drept
            return False
        return True


class Nod:
    with open('Input/input.txt') as fin:
        N = int(fin.readline())
        M = int(fin.readline())

    def __init__(self, canibali=N, misionari=N, pozitieBarca=0, parinte=None, succesori=[]):
        self.informatie = Info(canibali, misionari, pozitieBarca)
        self.parinte = parinte
        self.succesori = deepcopy(succesori)

    def __eq__(self, other):
        return self.informatie == other.informatie

    def __str__(self):
        return "Stare curenta:\n" + str(self.informatie)

    def __repr__(self):
        return repr(self.informatie)

    def drumRadacina(self):
        drum = [self]
        nod = self
        while nod.parinte is not None:
            drum = [nod.parinte] + drum
            nod = nod.parinte
        return drum

    def vizitat(self):
        return len([1 for nod in self.drumRadacina() if nod == self]) > 1

    def validState(self):
        return self.informatie.validState()

    def findSuccesori(self):
        for nrMisionari in range(0, self.M + 1):
            for nrCanibali in range(0, self.M - nrMisionari + 1):
                if nrMisionari == nrCanibali and nrMisionari == 0:  # skip, nu putem lua 0 oameni
                    continue
                if self.informatie.pozitieBarca == 0:  # stanga -> dreapta
                    pozitieBarca = 1
                    canibali = self.informatie.canibali - nrCanibali
                    misionari = self.informatie.misionari - nrMisionari
                else:  # dreapta -> stanga
                    pozitieBarca = 0
                    canibali = self.informatie.canibali + nrCanibali
                    misionari = self.informatie.misionari + nrMisionari
                if canibali < 0 or canibali > self.N or misionari < 0 or misionari > self.N:
                    continue
                nod = Nod(canibali, misionari, pozitieBarca, self)
                if nod.validState() and not nod.vizitat():
                    self.succesori.append(nod)
        return self.succesori


class Graf:
    def __init__(self, nodStart, noduriScop, muchii=[]):
        self.nodStart = nodStart
        self.noduriScop = noduriScop
        self.muchii = deepcopy(muchii)

    def scop(self, informatie):
        return informatie in self.noduriScop

    def succesori(self, nod):
        return nod.findSuccesori()


def bfs(graf, n):
    queue = [graf.nodStart]
    solutie = []
    while len(queue) > 0:
        nodCurent = queue.pop(0)
        if graf.scop(nodCurent):
            solutie.append(nodCurent)
            if len(solutie) == n:
                return solutie
        else:
            succesori = graf.succesori(nodCurent)
            queue.extend(deepcopy(succesori))
    return solutie


def printDrumRadacina(G, NSOL=2):
    solutie = bfs(G, NSOL)
    path = input()
    fout = open(path, "w")
    for nodScop in solutie:
        drum = nodScop.drumRadacina()
        fout.write("------- Solutie -------\n\n")
        currNod = drum[0]
        for i in range(1, len(drum)):
            fout.write(str(currNod) + "\n\n")
            fout.write(
                f"Pas {i}: Barca s-a deplasat de pe malul {'stang' if currNod.informatie.pozitieBarca == 0 else 'drept'}" +
                f" pe malul {'drept' if currNod.informatie.pozitieBarca == 0 else 'stang'} cu " +
                formatString(
                    abs(currNod.informatie.misionari - drum[i].informatie.misionari), 
                    abs(currNod.informatie.canibali - drum[i].informatie.canibali), 
                    " si "
                ) + "\n\n"
            )
            currNod = drum[i]
        fout.write(str(currNod) + "\n\n")
    fout.close()


G = Graf(Nod(), [Nod(0, 0, 1)])
printDrumRadacina(G)