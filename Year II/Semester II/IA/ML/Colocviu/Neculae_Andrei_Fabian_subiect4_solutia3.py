import math
import numpy as np


class KnnClassifier:
    def __init__(self, train_data, train_labels):
        self.train_data = train_data
        self.train_labels = train_labels

    def classify_signal(self, test_signal, num_neighbors=3, metric='l2'):
        if metric.lower() == 'l2':
            distances = np.sqrt(np.sum(((self.train_data - test_signal) ** 2), axis=1))
        else:
            distances = np.sum(np.abs(self.train_data - test_signal), axis=1)

        good = np.array(self.train_labels[distances.argsort()[:num_neighbors]], dtype='int64')
        return np.bincount(good).argmax()

    def clasify_signals(self, test_data, num_neighbors=3, metric='l2'):
        predictions = [self.classify_signal(signal, num_neighbors, metric) for signal in test_data]
        return np.array(predictions)


def load_train():
    PATH = "V4/data/"
    train_data = np.zeros((1000, 3, 155))
    train_labels = np.zeros(1000)
    i = 0

    with open(PATH + "train.txt", "r") as f:
        line = f.readline()
        while True:
            line = f.readline()
            if line == "":
                break
            file, train_label = line.split(",")
            with open(PATH + file, "r") as g:
                X = np.zeros(155)
                Y = np.zeros(155)
                Z = np.zeros(155)
                j = 0
                while True:
                    line = g.readline()
                    if line == "":
                        break
                    x, y, z = line.split(",")
                    X[j] = float(x)
                    Y[j] = float(y)
                    Z[j] = float(z)
                    j += 1
                train_data[i] = [X, Y, Z]
                train_labels[i] = train_label
                i += 1
    return train_data, train_labels

def load_test_lbl():
    PATH = "V4/data/"
    train_labels = np.zeros(400)
    i = 0

    with open(PATH + "test_labels.txt", "r") as f:
        line = f.readline()
        while True:
            line = f.readline()
            if line == "":
                break
            file, train_label = line.split(",")
            train_labels[i] = train_label
            i += 1
    return train_labels


def load_test():
    PATH = "V4/data/"
    test_data = np.zeros((400, 3, 155))
    i = 0

    with open(PATH + "test.txt", "r") as f:
        line = f.readline()
        while True:
            line = f.readline()
            if line == "":
                break
            line = line.split('\n')[0]
            with open(PATH + line, "r") as g:
                X = np.zeros(155)
                Y = np.zeros(155)
                Z = np.zeros(155)
                j = 0
                while True:
                    line = g.readline()
                    if line == "":
                        break
                    x, y, z = line.split(",")
                    X[j] = float(x)
                    Y[j] = float(y)
                    Z[j] = float(z)
                    j += 1
                test_data[i] = [X, Y, Z]
                i += 1
    return test_data


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
    good = np.zeros(k * k * 3)
    for i in range(k * k):
        good[i] = X[i]
        good[i + k * k] = Y[i]
        good[i + 2 * k * k] = Z[i]
    return good


def predict_split(train_data, train_labels, P):
    N = train_labels.shape[0]
    M = math.floor(P * N)
    return train_data[:M], train_labels[:M], train_data[M:], train_labels[M:]


def accuracy_score(labels, predicted_labels):
    return np.mean(labels == predicted_labels)


train_data, train_labels = load_train()
test_data = load_test()
test_labels = load_test_lbl()

train_encoded = np.zeros((1000, 75))
test_encoded = np.zeros((400, 75))
for i in range(train_data.shape[0]):
    train_encoded[i] = encode(train_data[i])
for i in range(test_data.shape[0]):
    test_encoded[i] = encode(test_data[i])

# train_split, train_labels_split, test_split, test_lables_split = predict_split(train_encoded, train_labels, 0.8)

model = KnnClassifier(train_encoded, train_labels)
predictions = model.clasify_signals(test_encoded, num_neighbors=3, metric='l2')
print(accuracy_score(test_labels, predictions) * 100)
with open('Neculae_Andrei_Fabian_subiect4_solutia3.txt', 'w') as f:
    for prediction in predictions:
        f.write(str(prediction) + '\n')
# print(accuracy_score(test_lables_split, predictions) * 100)
