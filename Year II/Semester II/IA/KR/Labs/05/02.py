def estimeaza_h(self, nod, euristica):
    if euristica == "banala":
        return 1 - self.scop(nod)
    elif euristica == "euristica mutari":
        if self.scop(nod):
            return 0
    elif euristica == "euristica costuri":
    elif euristica == "neadmisibila":
        return float('inf')
