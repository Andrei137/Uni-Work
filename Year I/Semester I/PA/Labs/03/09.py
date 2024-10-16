def dijkstra(n, graph, d, s):
    for i in range(n):
        d[i] = graph[0][i]
    s[1] = True
    while True:
        vertex = -1
        minimum = 1e6
        for i in range(n):
            if s[i] == 0 and d[i] < minimum:
                minimum = d[i]
                vertex = i
        if vertex == -1:
            break
        s[vertex] = True
        for i in range(n):
            if s[i] == 0 and d[i] > d[vertex] + graph[vertex][i]:
                d[i] = d[vertex] + graph[vertex][i]
    return d[n - 1]


n, m = map(int, input().split())
graph = [[int(1e6) for i in range(0, n)] for j in range(0, n)]
s = [False for i in range(n)]
for i in range(n):
    graph[i][i] = 0
for i in range(m):
    x, y, w = map(int, input().split())
    graph[x - 1][y - 1] = w
print(dijkstra(n, graph, [0 for i in range(n)], s))
