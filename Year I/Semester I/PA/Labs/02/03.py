def find_index(c, s, t):
    match c:
        case "find":
            i = s.find(t)
            while i != -1:
                print(i, end=' ')
                i = s.find(t, i + 1)
        case "index":
            i = -1
            while True:
                try:
                    i = s.index(t, i + 1)
                    print(i, end=' ')
                except ValueError:
                    break
        case _:
            pass


s, t = input().split()
c = input()
find_index(c, s, t)
