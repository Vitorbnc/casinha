import data
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.svm import LinearSVC
from sklearn.linear_model import SGDClassifier

import pickle
import os

(data_train, y_train) = data.load()
print(data_train)
print(y_train)
y_names =[]
[y_names.append(data.get_label_name(i)) for i in y_train]
print(y_names)
data.save(data_train,y_train)

model_path = 'model.bin'
model_path = os.path.join(os.path.dirname(__file__),model_path)

#I've found ngram_range = (1,2),(2,3),(3,4) works better
cv = CountVectorizer(ngram_range=(2,3),analyzer='char_wb')
x_train = cv.fit_transform(data_train)

def build_classifier():
    clf = LinearSVC()
    clf.fit(x_train,y_train)
    return clf

def load_classifier():
    if os.path.exists(model_path):
        clf = pickle.load(open(model_path))
        return clf
    else:
         return build_classifier()

def save_classifier(model):
    with open(model_path,'w+b') as f:
        pickle.dump(model,f)

clf = load_classifier()
#save_classifier(clf)

def predict(string_input):
    string_input = string_input.lower()
    x = cv.transform([string_input])
    #print(x)
    y = clf.predict(x)
    y = y[0]
    label = data.get_label_name(y)
    print("Predicted label:"+label)
    return label

#predict("levanta a base")
    





