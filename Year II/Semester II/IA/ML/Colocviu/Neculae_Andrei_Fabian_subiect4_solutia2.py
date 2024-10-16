import numpy as np


def encode(S, k=5):
    def get_bins(min_value, max_value, no_bins):
        return np.linspace(start=min_value, stop=max_value, num=no_bins)

    def values_to_bins(data, bins):
        return np.digitize(data, bins) - 1

    def encode_axis(S):
        bins = get_bins(np.min(S), np.max(S), k)
        for i in range(len(S)):
            S[i] = values_to_bins(S[i], bins)
        A = np.zeros((k, k))
        for i in range(len(S) - 1):
            A[int(S[i])][int(S[i + 1])] += 1
        for i in range(k):
            for j in range(k):
                line_sum = np.sum(A[i])
                if line_sum != 0:
                    A[i][j] /= np.sum(A[i])
        return A.reshape(-1)

    X = encode_axis(S[0])
    Y = encode_axis(S[1])
    Z = encode_axis(S[2])
    return X + Y + Z
