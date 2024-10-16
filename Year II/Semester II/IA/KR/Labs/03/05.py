from copy import deepcopy
import heapq


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

    def __init__(self, canibali=N, misionari=N, pozitieBarca=0, parinte=None, g=0, h=0, succesori=[]):
        self.informatie = Info(canibali, misionari, pozitieBarca)
        self.parinte = parinte
        self.g = g
        self.h = h
        self.f = g + h
        self.succesori = deepcopy(succesori)

    def __eq__(self, other):
        return self.informatie == other.informatie

    def __lt__(self, other):
        if self.f == other.f:
            return self.g < other.g
        return self.f < other.f

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

    def estimeaza_h(self):
        return (self.informatie.canibali + self.informatie.misionari) // 2

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
                nod = Nod(canibali, misionari, pozitieBarca, self, self.g + 1, self.estimeaza_h())
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


def a_star(graf):
    open_heap = [graf.nodStart]
    closed = {}
    while len(open_heap) > 0:
        nodCurent = heapq.heappop(open_heap)
        closed[repr(nodCurent.informatie)] = nodCurent
        if graf.scop(nodCurent):
            return nodCurent
        succesori = graf.succesori(nodCurent)
        for succesor in succesori:
            nodNou = None
            if succesor in open_heap:
                nodVechi = open_heap[open_heap.index(succesor)]
                if succesor < nodVechi:
                    open_heap.remove(nodVechi)
                    nodNou = succesor
            elif repr(succesor.informatie) in closed:
                if succesor < closed[repr(succesor.informatie)]:
                    closed.pop(repr(succesor.informatie))
                    nodNou = succesor
            else:
                nodNou = succesor
            if nodNou is not None:
                heapq.heappush(open_heap, nodNou)


def printDrumRadacina(G):
    nodScop = a_star(G)
    path = input()
    fout = open(path, "w")
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