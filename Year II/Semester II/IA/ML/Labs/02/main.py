from sklearn.naive_bayes import MultinomialNB
import numpy as np
import matplotlib.pyplot as plt

# 1
people = [(160, 'F'), (165, 'F'), (155, 'F'), (172, 'F'), (175, 'B'), (180, 'B'), (177, 'B'), (190, 'B')]
no_total = len(people)
females = [p for p in people if p[1] == 'F']
no_females = len(females)
no_interval3 = len([p for p in people if p[0] in range(171, 181)])
no_females_interval3 = len([f for f in females if f[0] in range(171, 181)])
prob_females = no_females / no_total
prob_interval3 = no_interval3 / no_total
prob_females_interval3 = no_females_interval3 / no_females
print(prob_females * prob_females_interval3 / prob_interval3)

# 2
def get_bins(no_bins):
    return np.linspace(start=0, stop=255, num=no_bins)

def values_to_bins(data, bins):
    return np.digitize(data, bins) - 1

train_images = np.loadtxt('data/train_images.txt')
train_labels = np.loadtxt('data/train_labels.txt', 'float')
test_images = np.loadtxt('data/test_images.txt')
test_labels = np.loadtxt('data/test_labels.txt', 'float')

# 3
bins = get_bins(5)
copy_train_images = values_to_bins(train_images, bins)
copy_test_images = values_to_bins(test_images, bins)
naive_bayes_model = MultinomialNB()
naive_bayes_model.fit(copy_train_images, train_labels)
naive_bayes_model.predict(copy_test_images)
print(naive_bayes_model.score(copy_test_images, test_labels) * 100)

# 4
no_bins = [3, 5, 7, 9, 11]
scores = []
for no_bin in no_bins:
    bins = get_bins(no_bin)
    copy_train_images = values_to_bins(train_images, bins)
    copy_test_images = values_to_bins(test_images, bins)
    naive_bayes_model.fit(copy_train_images, train_labels)
    scores.append(naive_bayes_model.score(copy_test_images, test_labels) * 100)
print(scores)

# 5
bins = get_bins(11)
copy_train_images = values_to_bins(train_images, bins)
copy_test_images = values_to_bins(test_images, bins)
naive_bayes_model.fit(copy_train_images, train_labels)
predictions = naive_bayes_model.predict(copy_test_images)
misplaced = [image for image in range(len(predictions)) if predictions[image] != test_labels[image]]
for i in range(10):
    print(f"Actual: {test_labels[misplaced[i]]} | Found: {predictions[misplaced[i]]}")
    image = test_images[misplaced[i]]
    image = np.reshape(image, (28, 28))
    plt.title("Imagine misclasata")
    plt.imshow(image.astype(np.uint8), cmap='gray')
    plt.show()
