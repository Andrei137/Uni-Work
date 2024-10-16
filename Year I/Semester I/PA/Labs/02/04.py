s = input()
slen = len(s)
for i in range((slen + 1) // 2):
    print(s[i:slen - i].center(slen))