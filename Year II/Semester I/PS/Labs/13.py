import numpy as np


def ex_1(l, t, no_simulations=100000):
    d = (t / 2) * np.random.random(no_simulations)
    theta = (np.pi / 2) * np.random.random(no_simulations)
    print(f"Pi este {no_simulations / sum(d <= l / 2 * np.sin(theta))}")


print("< Choose exercise to run >")
print("[1]")
method_choice = input("-> ")
if method_choice == '1':
    ex_1(1, 2)
