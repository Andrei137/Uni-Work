def backtracking(A, S, submultiset, index):
    # S == 0 <--> a fost gasita o solutie corecta
    if S == 0:
        print(submultiset)
    # daca s-a ajuns la finalul listei sau suma a devenit negativa, se opreste backtracking-ul
    elif index >= len(A) or S < 0:
        return
    else:
        # urmatorul pas fara elementul A[index]
        backtracking(A, S, submultiset, index + 1)
        # urmatorul pas cu elementul A[index]m care se scade din suma
        backtracking(A, S - A[index], submultiset + [A[index]], index + 1)


A = [int(x) for x in input().split()]
S = int(input())
backtracking(A, S, [], 0)
