import numpy as np
import matplotlib.pyplot as plt

class KnnClassifier:
    # 1
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    # 2
    def classify_image(self, test_image, num_neighbors = 3, metric='l2'):
        if metric.lower() == 'l2':
            distances = np.sqrt(np.sum(((self.train_images - test_image) ** 2), axis=1))
        else:
            distances = np.sum(np.abs(self.train_images - test_image), axis=1)

        return np.bincount(self.train_labels[distances.argsort()[:num_neighbors]]).argmax()

    def clasify_images(self, test_images, num_neighbors=3, metric='l2'):
        predictions = [self.classify_image(image, num_neighbors, metric) for image in test_images]
        return np.array(predictions)

# 3
def accuracy_score(labels, predicted_labels):
    return np.mean(labels == predicted_labels)

train_images = np.loadtxt('./data/train_images.txt')
train_labels = np.int32(np.loadtxt('./data/train_labels.txt'))

test_images = np.loadtxt('./data/test_images.txt')
test_labels = np.int32(np.loadtxt('./data/test_labels.txt'))

model = KnnClassifier(train_images, train_labels)
predictions = model.clasify_images(test_images, num_neighbors=3, metric='l2')
with open('./txt/predictii_3nn_l2_mnist.txt', 'w') as f:
    f.write(f'Accuracy is {accuracy_score(test_labels, predictions) * 100}')

# 4
def get_accuracy(model, test_images, metric):
    accuracies = []
    for i in range(1, 10, 2):
        predictions = model.clasify_images(test_images, num_neighbors=i, metric=metric)
        accuracies.append(accuracy_score(test_labels, predictions))
    return accuracies

acc_l1 = get_accuracy(model, test_images, 'l1')
acc_l2 = get_accuracy(model, test_images, 'l2')

with open('./txt/acuratete_l2.txt', 'w') as f:
    f.write('l1\n')
    for accuracy in acc_l1:
        f.write(f'{accuracy}\n')
    f.write('\nl2\n')
    for accuracy in acc_l2:
        f.write(f'{accuracy}\n')

plt.plot(range(1, 10, 2), acc_l1, label='l1')
plt.show()

plt.plot(range(1, 10, 2), acc_l1, label='l2')
plt.show()