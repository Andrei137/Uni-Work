s = input()
name = "".join(s.replace("-", " ").split())
if not name.isalpha():
    print("Nume invalid")
else:
    i = s.count("-")
    s = s.split()
    if len(s) != 2 or i > 2:
        print("Nume invalid")
    else:
        is_valid = True
        for i in s:
            j = i.find("-")
            if (j == -1 and len(i) < 3) or (j != -1 and len(i[:j - 1]) < 3 or len(i[j + 1:]) < 3):
                is_valid = False
        for i in range(len(s)):
            s[i] = ' ' + s[i] + ' '
            for j in range(1, len(s[i])):
                if s[i][j - 1] == ' ' or s[i][j - 1] == '-':
                    if not s[i][j].isupper():
                        is_valid = False
                        break
            else:
                curr_name = s[i].split(" -")
                for j in range(len(curr_name)):
                    if len(curr_name[j]) < 3:
                        is_valid = False
                        break
        if is_valid:
            print("Nume valid")
        else:
            print("Nume invalid")
