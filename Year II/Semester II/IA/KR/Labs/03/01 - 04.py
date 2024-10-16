'''
graf = Graf(0,
            [4, 6],
            [(0, 1, 3), (0, 2, 50), (0, 3, 100), (0, 6, 1000),
             (1, 3, 4), (2, 3, 4), (2, 4, 9), (2, 5, 3),
             (3, 1, 3), (3, 4, 2), (5, 4, 4), (6, 2, 3)],
            {1: 1, 2: 6, 3: 2, 4: 0, 5: 3, 6: 0})

graf = Graf(0,
            [4, 6],
            [(0, 1, 3), (0, 2, 5), (0, 3, 10), (0, 6, 100),
             (1, 3, 4), (2, 3, 4), (2, 4, 1), (2, 5, 3),
             (3, 1, 3), (3, 4, 2), (5, 4, 4), (6, 2, 3)],
            {1: 1, 2: 6, 3: 2, 4: 0, 5: 3, 6: 0})
'''


from copy import deepcopy
import heapq
import time


class Nod:
    def __init__(self, informatie, parinte=None, g=0, h=0, succesori=[]):
        self.informatie = informatie
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
    def __init__(self, nodStart, noduriScop, muchii=[], estimari=[]):
        self.nodStart = Nod(nodStart)
        self.noduriScop = noduriScop
        self.muchii = deepcopy(muchii)
        self.estimari = deepcopy(estimari)

    def scop(self, informatie):
        return informatie in self.noduriScop

    def estimeaza_h(self, nod):
        return self.estimari[nod]

    def succesori(self, nod):
        if nod.succesori:
            return nod.succesori
        if nod.informatie not in self.muchii:
            return []
        nod.succesori = [Nod(nodInfo, nod, nod.g + cost, self.estimeaza_h(nodInfo)) for (nodInfo, cost) in self.muchii[nod.informatie] if not Nod(nodInfo, nod).vizitat()]
        return nod.succesori


def a_star(graf):
    open_list = [graf.nodStart]
    closed = []
    while len(open_list) > 0:
        nodCurent = open_list[0]
        open_list = open_list[1:]
        closed.append(nodCurent)
        if graf.scop(nodCurent.informatie):
            return nodCurent
        succesori = graf.succesori(nodCurent)
        for succesor in succesori:
            nodNou = None
            if succesor in open_list:
                nodVechi = open_list[open_list.index(succesor)]
                if succesor < nodVechi:
                    open_list.remove(nodVechi)
                    nodNou = succesor
            elif succesor in closed:
                nodVechi = closed[closed.index(succesor)]
                if succesor < nodVechi:
                    closed.remove(nodVechi)
                    nodNou = succesor
            else:
                nodNou = succesor
            if nodNou is not None:
                open_list.append(nodNou)
                open_list.sort()


def a_star_heap(graf):
    open_heap = [graf.nodStart]
    closed = {}
    while len(open_heap) > 0:
        nodCurent = heapq.heappop(open_heap)
        closed[nodCurent.informatie] = nodCurent
        if graf.scop(nodCurent.informatie):
            return nodCurent
        succesori = graf.succesori(nodCurent)
        for succesor in succesori:
            nodNou = None
            if succesor in open_heap:
                nodVechi = open_heap[open_heap.index(succesor)]
                if succesor < nodVechi:
                    open_heap.remove(nodVechi)
                    nodNou = succesor
            elif succesor.informatie in closed:
                if succesor < closed[succesor.informatie]:
                    closed.pop(succesor.informatie)
                    nodNou = succesor
            else:
                nodNou = succesor
            if nodNou is not None:
                heapq.heappush(open_heap, nodNou)


def ida_star(graf, n=1):
    def expandeaza(graf, nodCurent, limita, found, n):
        if n <= 0:
            return (float('inf'), 0)
        if nodCurent.f > limita:
            return (nodCurent.f, n)
        if graf.scop(nodCurent.informatie) and repr(nodCurent) not in found:
            print(repr(nodCurent))
            n -= 1
            found[repr(nodCurent)] = 1
        succesori = graf.succesori(nodCurent)
        minim = float('inf')
        for succesor in succesori:
            (lim_succesor, n) = expandeaza(graf, succesor, limita, found, n)
            if lim_succesor < minim:
                minim = lim_succesor
        return (minim, n)

    found = {}
    N_MAX = float('inf')
    limita = graf.estimeaza_h(graf.nodStart.informatie)
    nodCurent = graf.nodStart
    while n > 0 and limita != N_MAX:
        (limita, n) = expandeaza(graf, nodCurent, limita, found, n)


G = Graf(0, [4, 6], {0: [(1, 3), (2, 5), (3, 10), (6, 100)], 1: [(3, 4)], 2: [(3, 4), (4, 9), (5, 3)], 3: [(1, 3), (4, 2)], 5: [(4, 4), (6, 5)], 6: [(2, 3)]}, {0: 5, 1: 1, 2: 6, 3: 2, 4: 0, 5: 3, 6: 0})
t1 = time.time()
print(repr(a_star(G)))
t2 = time.time()
print("A* cu liste : " + str(t2 - t1))
t1 = time.time()
print(repr(a_star_heap(G)))
t2 = time.time()
print("A* cu heap si dict : " + str(t2 - t1))
ida_star(G)
