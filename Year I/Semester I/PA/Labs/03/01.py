def is_correct(line):
    i, j = line.find('*'), line.find('=')
    return (int(line[:i]) * int(line[i + 1:j]) is int(line[j + 1:]))


fin = open("Txt Files/test.in")
fout = open("Txt Files/test.out", "w")
nota = 1
for line in fin.readlines():
    endl = line.find('\n')
    fout.write(line[:endl])
    if is_correct(line):
        nota += 1
        fout.write(" Corect")
    else:
        i, j = line.find('*'), line.find('=')
        fout.write(f" Gresit {int(line[:i]) * int(line[i + 1:j])}")
    fout.write('\n')
fin.close()
fout.write(f"Nota {nota}")
fout.close()
