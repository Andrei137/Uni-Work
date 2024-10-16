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
    def __init__(self, nodStart, noduriScop, muchii=[], estimari=[]):
        self.nodStart = Nod(nodStart)
        self.noduriScop = noduriScop
        self.muchii = deepcopy(muchii)
        self.estimari = deepcopy(estimari)

    def scop(self, informatie):
        return informatie in self.noduriScop

    def estimeaza(self, nod):
        return self.estimari[nod]

    def succesori(self, nod):
        if nod.succesori:
            return nod.succesori
        if nod.informatie not in self.muchii:
            return []
        nod.succesori = sorted([Nod(nodInfo, nod) for (nodInfo, _) in self.muchii[nod.informatie] if not Nod(nodInfo, nod).vizitat()], key=lambda x: x.informatie)
        return nod.succesori

    def minimax(self, nod, depth, alpha, beta, max_player):
        if depth == 0 or self.scop(nod.informatie):
            return self.estimeaza(nod.informatie), nod
        succesori = self.succesori(nod)
        best = None
        if max_player:
            value = -float('inf')
            for succesor in succesori:
                new_value, new_best = self.minimax(succesor, depth - 1, alpha, beta, False)
                if new_value > value:
                    value = new_value
                    best = succesor
                alpha = max(alpha, value)
                if beta <= alpha:
                    break
        else:
            value = float('inf')
            for succesor in succesori:
                new_value, new_best = self.minimax(succesor, depth - 1, alpha, beta, True)
                if new_value < value:
                    value = new_value
                    best = succesor
                beta = min(beta, value)
                if beta <= alpha:
                    break
        return value, best

    def print_sol(self):
        nod = self.nodStart
        depth = 10
        max_player = True
        while not self.scop(nod.informatie):
            value, nod = self.minimax(nod, depth, -float('inf'), float('inf'), max_player)
            depth -= 1
            max_player = not max_player
        print(value, [nod])


G = Graf(0, 
        [2, 5, 6, 7, 9, 10], 
        {0: [(1, 1), (2, 1), (3, 1)], 
         1: [(4, 1), (5, 1)],  
         3: [(8, 1), (9, 1)], 
         4: [(6, 1), (7, 1)], 
         8: [(10, 3)]},
        {0: None, 1: None, 2: float('-inf'), 3: None, 4: None, 5: 0, 6: 3, 7: 2, 8: None, 9: float('inf'), 10: 1})
G.print_sol()
