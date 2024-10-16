import numpy as np
from sklearn import preprocessing
from sklearn import svm
from sklearn.metrics import f1_score, classification_report


# 2
def normalize_data(train_data, test_data, normalization_type=None):
    if normalization_type is None:
        return train_data, test_data
    if normalization_type == 'standard':
        scaler = preprocessing.StandardScaler()
    else:
        scaler = preprocessing.Normalizer(norm=normalization_type)
    scaler.fit(train_data)
    scaled_train_data = scaler.transform(train_data)
    scaled_test_data = scaler.transform(test_data)
    return scaled_train_data, scaled_test_data


# 3
class BagOfWords:
    def __init__(self):
        self.words = {}
        self.words_in_order = []

    def build_vocabulary(self, data):
        for document in data:
            for word in document:
                if word not in self.words.keys():
                    self.words_in_order.append(word)
                    self.words[word] = len(self.words)

        print(f"Length of vocabulary: {len(self.words)}")
        self.words['__unknown__'] = len(self.words)

    # 4
    def get_features(self, data):
        features = np.zeros((len(data), len(self.words)))
        for idx, document in enumerate(data):
            for word in document:
                if word in self.words:
                    features[idx][self.words[word]] += 1
                else:
                    features[idx][self.words['__unknown__']] += 1
        return features


# 5
def accuracy_score(labels, predicted_labels):
    return np.mean(labels == predicted_labels)


training_data = np.load('./data/training_sentences.npy', allow_pickle=True)
training_labels = np.load('./data/training_labels.npy', allow_pickle=True)

test_data = np.load('./data/test_sentences.npy', allow_pickle=True)
test_labels = np.load('./data/test_labels.npy', allow_pickle=True)

bow = BagOfWords()
bow.build_vocabulary(training_data)

train_features = bow.get_features(training_data)
test_features = bow.get_features(test_data)
print(train_features.shape)
print(test_features.shape)
scaled_train_data, scaled_test_data = normalize_data(train_features, test_features, normalization_type='l2')


# 6
svm_model = svm.SVC(C=1, kernel='linear')
svm_model.fit(scaled_train_data, training_labels)
predicted_labels = svm_model.predict(scaled_test_data)
accuracy = accuracy_score(test_labels, predicted_labels)
print(f"f1 score: {f1_score(test_labels, predicted_labels) * 100}")
print(f"Accuracy: {accuracy * 100}")
print(classification_report(test_labels, predicted_labels))
idx = np.argsort(svm_model.coef_[0])
print('The first 10 negative words are:', [bow.words_in_order[i] for i in idx[:10]])
print('The first 10 positive words are:', [bow.words_in_order[i] for i in idx[-10:]])
