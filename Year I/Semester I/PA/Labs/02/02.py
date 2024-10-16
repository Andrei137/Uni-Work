s = input()
c = s[0]
s = s.replace(c, '')
format_print = "Dupa stergerea literei \'{0}\', sirul obtinut este \"{1}\" de lungime {2}"
print(format_print.format(c, s, len(s)))
