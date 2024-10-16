import numpy as np
import matplotlib.pyplot as plt


def cmp(nr_simulari, sansa):
    return np.random.random(nr_simulari) <= sansa


def ex_1():
    plt.style.use('dark_background')
    ax = plt.gca()
    ax.cla()
    ax.set_aspect('equal', 'box')
    ax.set_xlim((0, 1))
    ax.set_ylim((0, 1))

    nr_simulari = 10000

    corecte = cmp(nr_simulari, 0.5)
    sp_corecte = np.cumsum(corecte)
    probabilitate_corecte = sp_corecte / range(1, nr_simulari + 1)

    masluite = cmp(nr_simulari, 0.75)
    sp_masluite = np.cumsum(masluite)
    probabilitate_masluite = sp_masluite / range(1, nr_simulari + 1)

    for i in range(nr_simulari):
        ax.cla()
        ax.add_patch(plt.Rectangle((0, 0), 0.25, probabilitate_corecte[i], facecolor="blue"))
        ax.add_patch(plt.Rectangle((0.25, 0), 0.25, 1 - probabilitate_corecte[i], facecolor="red"))
        ax.add_patch(plt.Rectangle((0.5, 0), 0.25, probabilitate_masluite[i], facecolor="blue"))
        ax.add_patch(plt.Rectangle((0.75, 0), 0.25, 1 - probabilitate_masluite[i], facecolor="red"))
        plt.pause(0.01)
    plt.show()


def ex_2():
    plt.style.use('dark_background')
    ax = plt.gca()
    ax.cla()
    ax.set_aspect('equal', 'box')
    ax.set_xlim((0, 1))
    ax.set_ylim((0, 1))

    nr_simulari = 10000

    corecte = 1 + (np.random.random(nr_simulari) * 6).astype(int)
    probabilitate_corecte = [(corecte == i).cumsum() / range(1, nr_simulari + 1) for i in range(1, 7)]

    for i in range(nr_simulari):
        ax.cla()
        ax.add_patch(plt.Rectangle((0, 0), 1 / 6, probabilitate_corecte[0][i], facecolor="red"))
        ax.add_patch(plt.Rectangle((1 / 6, 0), 1 / 6, probabilitate_corecte[1][i], facecolor="orange"))
        ax.add_patch(plt.Rectangle((2 / 6, 0), 1 / 6, probabilitate_corecte[2][i], facecolor="yellow"))
        ax.add_patch(plt.Rectangle((3 / 6, 0), 1 / 6, probabilitate_corecte[3][i], facecolor="green"))
        ax.add_patch(plt.Rectangle((4 / 6, 0), 1 / 6, probabilitate_corecte[4][i], facecolor="blue"))
        ax.add_patch(plt.Rectangle((5 / 6, 0), 1 / 6, probabilitate_corecte[5][i], facecolor="purple"))
        plt.pause(0.01)
    plt.show()


ex_2()
