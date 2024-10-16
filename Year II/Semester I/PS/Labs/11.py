import numpy as np
import matplotlib.pyplot as plt


def ex_1(lmbd, no_simulations=1000):
    x = -1 / lmbd * np.log(np.random.random(no_simulations))
    plt.hist(x, bins=30, ec="yellow", color="red", density=True)
    a = np.linspace(0, 30, 1000)
    b = lmbd * np.exp(-lmbd * a)
    plt.plot(a, b, color="blue")
    plt.show()


def ex_2(gama, x0, no_simulations=1000):
    x = x0 + gama * np.tan(np.pi * (np.random.random(no_simulations) - 1 / 2))
    plt.hist(x, bins=30, ec="yellow", color="red", density=True, range=(-10, 10))
    a = np.linspace(-10, 10, 1000)
    b = (gama / np.pi) * (1 / (gama ** 2 + (a - x0) ** 2))
    plt.plot(a, b, color="blue")
    plt.show()


print("< Choose exercise to run >")
print("[1]")
print("[2]")
method_choice = input("-> ")
if method_choice == '1':
    ex_1(1 / 2)
elif method_choice == '2':
    ex_2(1, 0)
