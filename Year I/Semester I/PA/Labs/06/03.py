with open("Txt Files/harti.in", "r") as f:
    lines = f.readlines()
N = int(lines[0].strip())
L = [[int(line.split()[0]), int(line.split()[1])] for line in lines[1:]]
adj = [[] for _ in range(N + 1)]
for p in L:
    adj[p[0]].append(p[1])
    adj[p[1]].append(p[0])
st = []


def bkt(p):
    if p == N + 1:
        print(st)
        return
    for color in range(1, 5):
        can = True
        for v in adj[p]:
            if v < p and st[v - 1] == color:
                can = False
        if can:
            st.append(color)
            bkt(p + 1)
            st.pop()


bkt(1)
