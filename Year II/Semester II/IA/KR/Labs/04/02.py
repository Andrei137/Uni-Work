from copy import deepcopy
import heapq


class Info:
    def __init__(self, board):
        def total(board):
            def euristic(board):
                score = 0
                if board.count('0') == 3:
                    return float('-inf')
                elif board.count('X') == 3:
                    return float('inf')

                if board.count(' ') != 3:
                    if board.count('X') == 0:
                        if board.count('0') == 1:
                            score -= 1
                        else:
                            score -= 10
                    elif board.count('0') == 0:
                        if board.count('X') == 1:
                            score += 1
                        else:
                            score += 10

                return score

            score = 0
            for i in range(3):
                score += euristic(board[i])
            for i in range(3):
                score += euristic([board[0][i], board[1][i], board[2][i]])
            score += euristic([board[0][0], board[1][1], board[2][2]])
            score += euristic([board[0][2], board[1][1], board[2][0]])
            return score

        self.board = [[x for x in y] for y in board]
        self.euristica = total(self.board)

    def succesori(self, character):
        suc = []
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == ' ':
                    temp = deepcopy(self.board)
                    temp[i][j] = character
                    suc.append(Info(temp))
        return suc

    def __str__(self):
        return '\n'.join([''.join(s) for s in self.board])

    def __lt__(self, other):
        return self.euristica < other.euristica


class Nod:
    def __init__(self, board, parinte=None):
        self.board = board
        self.parinte = parinte

    def __str__(self):
        return f'{aux.join([repr(x) for x in self.drumRadacina()])}'

    def __repr__(self):
        return str(self.board)

    def drumRadacina(self):
        drum = []
        if self.parinte:
            drum = self.parinte.drumRadacina()
        drum.append(self)
        return l

    def __lt__(self, other):
        return self.board < other.board

    def euristica(self):
        return self.board.euristica

    def scop(self):
        return abs(self.euristica()) > Graf.oo // 2

    def succesori(self, character):
        return [Nod(nextInfo, self) for nextInfo in self.board.succesori(character)]


class Graf:
    oo = 1_000_000

    def __init__(self):
        self.nodStart = Nod(Info([[' ', ' ', ' '] for _ in range(3)]))

    def scop(self, nod):
        return nod.scop()

    def succesori(self, nod, character):
        return nod.succesori(character)

    def minimax(self, nod, depth=9, maxPlayer=True):
        if depth == 0 or self.scop(nod):
            return nod

        character = 'X' if maxPlayer else '0'
        states = [self.minimax(suc, depth - 1, not maxPlayer) for suc in self.succesori(nod, character)]

        if maxPlayer:
            return max(states)
        return min(states)


graf = Graf()
print(graf.minimax(graf.nodStart))
