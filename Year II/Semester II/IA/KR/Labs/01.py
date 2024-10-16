from copy import deepcopy


class Nod:
    def __init__(self, informatie, parinte=None, succesori=[]):
        self.informatie = informatie
        self.parinte = parinte
        self.succesori = deepcopy(succesori)

    def __eq__(self, other):
        return self.informatie == other.informatie

    def __str__(self):
        return str(self.informatie)

    def __repr__(self):
        if self.parinte is None:
            return str(self.informatie)
        return str(self.informatie) + " (" + " -> ".join([str(node) for node in self.drumRadacina()]) + ")"

    def drumRadacina(self):
        drum = [self]
        nod = self
        while nod.parinte is not None:
            drum = [nod.parinte] + drum
            nod = nod.parinte
        return drum

    def vizitat(self):
        return len([1 for nod in self.drumRadacina() if nod == self]) > 1


class Graf:
    def __init__(self, nodStart, noduriScop, muchii=[]):
        self.nodStart = Nod(nodStart)
        self.noduriScop = noduriScop
        self.muchii = deepcopy(muchii)

    def scop(self, informatie):
        return informatie in self.noduriScop

    def succesori(self, nod):
        if nod.succesori:
            return nod.succesori
        if nod.informatie not in self.muchii:
            return []
        nod.succesori = sorted([Nod(nodInfo, nod) for (nodInfo, _) in self.muchii[nod.informatie] if not Nod(nodInfo, nod).vizitat()], key=lambda x: x.informatie)
        return nod.succesori


def bfs(graf, n):
    queue = [graf.nodStart]
    solutie = []
    while len(queue) > 0:
        nodCurent = queue.pop(0)
        if graf.scop(nodCurent.informatie):
            solutie.append(nodCurent)
            if len(solutie) == n:
                return solutie
        else:
            succesori = graf.succesori(nodCurent)
            queue.extend(deepcopy(succesori))
    return solutie


def dfs(graf, n):
    stack = [graf.nodStart]
    solutie = []
    while len(stack) > 0:
        nodCurent = stack.pop()
        if graf.scop(nodCurent.informatie):
            solutie.append(nodCurent)
            if len(solutie) == n:
                return solutie
        else:
            succesori = graf.succesori(nodCurent)
            succesori.reverse()
            stack.extend(deepcopy(succesori))
    return solutie


G = Graf(0, [4, 6], {0: [(1, 3), (2, 5), (3, 10), (6, 100)], 1: [(3, 4)], 2: [(3, 4), (4, 9), (5, 3)], 3: [(1, 3), (4, 2)], 5: [(4, 4), (6, 5)], 6: [(2, 3)]})
n = int(input("n = "))
print("bfs : " + str(bfs(G, n)))
print("dfs : " + str(dfs(G, n)))
