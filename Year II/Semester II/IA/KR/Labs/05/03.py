def estimeaza_h(self, nod, euristica):
    final_pos = {1:(0, 0), 2:(0, 1), 3:(0, 2), 4:(1, 0), 5:(1, 1), 6:(1, 2), 7:(2, 0), 8:(2, 1), 9:(2, 2)}
    if euristica == "banala":
        return 1 - self.scop(nod)
    elif euristica == "euristica mutari":
        if self.scop(nod):
            return 0
        np = 0
        for i in range(3):
            for j in range(3):
                if nod.board[i][j] != 3 * i + j:
                    np += 1
        return np - 1 - (nod.board[2][2] != 0)
    elif euristica == "euristica costuri":
        np = 0
        for i in range(3):
            for j in range(3):
                if nod.board[i][j] != 3 * i + j:
                    np += nod.board[i][j]
        return np
    elif euristica == "euristica manhattan":
        np = 0
        for i in range(3):
            for j in range(3):
                if nod.board[i][j] != 0:
                    np += abs(final_pos[nod.board[i][j]][0] - i) + abs(final_pos[nod.board[i][j]][1] - j)
        return np
    elif euristica == "euristica manhattan costuri":
        final_pos = {1:(0, 0), 2:(0, 1), 3:(0, 2), 4:(1, 0), 5:(1, 1), 6:(1, 2), 7:(2, 0), 8:(2, 1), 9:(2, 2)}
        np = 0
        for i in range(3):
            for j in range(3):
                if nod.board[i][j] != 0:
                    np += nod.board[i][j] * (abs(final_pos[nod.board[i][j]][0] - i) + abs(final_pos[nod.board[i][j]][1] - j))
        return np
    elif euristica == "euristica neadmisibila":
        return float("inf")
