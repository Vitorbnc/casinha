import os
from sklearn.feature_extraction.text import HashingVectorizer
from sklearn.feature_extraction.text import CountVectorizer
import pickle
import sys

'''
Run classifier.py u h to update dataset files and use hashing, respectively 
Running without arguments will use regular count vectorizer and load saved pickle files
'''

train_data_path = 'train_data.txt'
labels_path = 'labels.txt'

pickled_data_train='data_train.bin'
pickled_y_train='y_train.bin'

current_dir = os.path.dirname(__file__)

train_data_path =os.path.join(os.path.dirname(__file__),train_data_path)
labels_path = os.path.join(os.path.dirname(__file__),labels_path)

pickled_data_train = os.path.join(os.path.dirname(__file__),pickled_data_train)
pickled_y_train = os.path.join(os.path.dirname(__file__),pickled_y_train)


x_train_str =[]
y_train = None
labels = []
x_train = None 

vect_ngram_range=(2,2)
vect_analyzer='char_wb'

hv = HashingVectorizer(ngram_range=vect_ngram_range, analyzer=vect_analyzer)
cv = CountVectorizer(ngram_range=vect_ngram_range,analyzer=vect_analyzer)


def load_dataset():
    global x_train_str
    global y_train
    global data_train
    global labels
    global pickled_data_available

    with open(labels_path) as f:
        [labels.append(line.replace('\n','').replace('\r','')) for line in f]

    pickled_data_available = False

    if os.path.exists(pickled_data_train):
         data_train = pickle.load(open(pickled_data_train,'r+b'))

    
    if os.path.exists(pickled_y_train):
         y_train = pickle.load(open(pickled_y_train,'r+b'))
         
    if x_train!=None and y_train!=None:
        print('Unpickled train data and labels')
        pickled_data_available = True
        
    if update_datasets:
        y_train=[]

        #Take special care with files or strings containing accents or characters like 'ç'. Open in binary mode and decode them with byte_array_object.decode('utf-8')
        with open(train_data_path,'r+b') as f:
            for line in f:
                line = line.decode('UTF-8')
                x,y =line.replace('\n','').replace('\r','').split(';')
                y = labels.index(y)
                x_train_str.append(x)
                y_train.append(y)

def save_dataset():
    data = open(pickled_data_train,'w+b')
    labels = open(pickled_y_train,'w+b')
    pickle.dump(x_train,data)
    pickle.dump(y_train,labels)
    data.close()
    labels.close()
    print('Train data saved')



update_datasets = 'u' in sys.argv
use_hashing = 'h' in sys.argv

if __name__ == "__main__":

    #global labels
    #global x_train

    load_dataset()

    if not pickled_data_available or update_datasets:
        if use_hashing:
            x_train = hv.transform(x_train_str)
            print(x_train.shape)

        else:
            x_train = cv.fit_transform(x_train_str)
            print(x_train.shape)
            print(cv.get_feature_names())

        save_dataset()


    print(x_train.shape)
    print(y_train)
    print(len(y_train))
    print(labels)
    