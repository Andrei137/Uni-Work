import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm


def ex_1_slow(no_simulations=5000):
    for _ in range(no_simulations):
        curr_x = curr_y = 0
        for _ in range(10):
            choice = np.random.random() < 0.5
            if choice == 0:
                next_y = curr_y - 1
            else:
                next_y = curr_y + 1
            next_x = curr_x + 1
            plt.plot([curr_x, next_x], [curr_y, next_y], color='blue', alpha=0.01)
            [curr_x, curr_y] = [next_x, next_y]
    plt.show()


def ex_1_a(no_simulations=10000):
    x = np.array([])
    for i in range(11):
        x = np.append(x, i)
    for i in range(no_simulations):
        y = np.append(np.array([0]), ((np.random.random(10) < 0.5) * 2 - 1).cumsum())
        plt.plot(x, y, color='blue', alpha=0.01)
    plt.show()


def ex_1_b(no_simulations=10000):
    final_pos = np.array([])
    for _ in range(no_simulations):
        final_pos = np.append(final_pos, ((np.random.random(10) < 0.5) * 2 - 1).cumsum()[-1])
    bins = np.array([np.unique(final_pos) - 1])
    bins = np.append(bins, [np.max(final_pos) + 1])
    plt.hist(final_pos, bins=bins.tolist(), color='blue', density=True)
    a = np.linspace(-10, 10, 1000)
    plt.plot(a, norm.pdf(a, 0, 3.1))
    plt.show()


print("< Choose exercise to run >")
print("[1] 1 a")
print("[2] 1 b")
method_choice = input("-> ")
if method_choice == '1':
    ex_1_a()
elif method_choice == '2':
    ex_1_b()
