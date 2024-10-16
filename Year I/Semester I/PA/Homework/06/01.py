from queue import PriorityQueue

# spec_queue -> (ora sfarsit, ora inceput, spec_nr)
spec_queue = PriorityQueue()
spec_nr = 1

fin = open("Txt Files/spectacole.in")
for linie in fin:
    temp = linie.split("-")
    # temp[1] -> ora sfarsit
    # temp[0] -> ora inceput
    spec_queue.put((temp[1].strip(), temp[0].strip(), spec_nr))
    spec_nr = spec_nr + 1
fin.close()

spec_curent = spec_queue.get()
# initializare cu primul spectacol, care va avea loc mereu
spec_optim = [spec_curent]
while not spec_queue.empty():
    spec_curent = spec_queue.get()
    # daca spectacolul curent incepe dupa ultimul programat, se adauga in lista
    if spec_curent[1] >= spec_optim[len(spec_optim) - 1][0]:
        spec_optim.append(spec_curent)

fout = open("Txt Files/programare.in", "w")
fout.write("Numarul maxim de spectacole: " + str(len(spec_optim)) + "\n")
fout.write("\nSpectacolele programate:\n")
for element in spec_optim:
    fout.write(element[1] + "-" + element[0] + " Spectacol " + str(element[2]) + "\n")
fout.close()
