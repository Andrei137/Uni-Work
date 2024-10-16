def correct(c, s, wrong, right):
    if wrong not in s:
        print("Nu exista greseli in sir")
    elif c == 'a':
        s = s.replace(wrong, right)
        print(s)
    elif c == 'b':
        count = 0
        while wrong in s:
            s = s.replace(wrong, right, 1)
            count += 1
        if count <= 2:
            print(s)
        else:
            print("Textul contine prea multe greseli, doar 2 au fost corectate")
    else:
        pass


s = input()
wrong, right = input().split()
c = input()
correct(c, s, wrong, right)
