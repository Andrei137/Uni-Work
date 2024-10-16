import numpy as np
import matplotlib.pyplot as plt


def bernoulli(p, no_simulations=10000):
    return np.random.choice([0, 1], no_simulations, p=[1 - p, p])


def bin(n, p, no_simulations=10000):
    return (np.random.random((no_simulations, n)) < p).sum(axis=1)


def geom(p, no_simulations=10000):
    arr = []
    for i in range(no_simulations):
        cnt = 1
        while np.random.random() > p:
            cnt += 1
        arr.append(cnt)


def ex2_bernoulli():
    x = bernoulli(0.5)
    bins = [-0.5, 0.5, 1.5]
    counts = np.histogram(x, bins)
    plt.hist(x, bins, ec='black', density=True)
    plt.xticks([0, 1])
    plt.show()


def ex2_binomial(n=100):
    x = bin(n, 0.5)
    bins = np.arange(0, n + 2) - 0.5
    counts = np.histogram(x, bins)
    plt.hist(x, bins, ec='black', density=True)
    plt.xticks(np.arange(0, n + 1))
    plt.show()


def ex2_geometric():
    x = geom(0.5)
    bins = np.arange(1, np.max(x) + 2) - 0.5
    counts = np.histogram(x, bins)
    plt.hist(x, bins, ec='black', density=True)
    plt.xticks(np.arange(1, np.max(x) + 1))
    plt.show()


def ex3(x, p, no_simulations=10000):
    bins = np.arange(1, len(x) + 2) - 0.5
    plt.hist(np.random.choice(x, no_simulations, p=p), bins, ec='black', density=True)
    plt.xticks(np.arange(0, len(x) + 2))
    plt.show()


print("< Choose exercise to run >")
print("[0] 2 Bernoulli")
print("[1] 2 Binomial")
print("[2] 2 Geometric")
print("[3] 3")
method_choice = input("-> ")
if method_choice == '0':
    ex2_bernoulli()
elif method_choice == '1':
    ex2_binomial()
elif method_choice == '2':
    ex2_geometric()
elif method_choice == '3':
    ex3([1, 2, 3, 4, 5], [0.1, 0.1, 0.6, 0.2, 0])
