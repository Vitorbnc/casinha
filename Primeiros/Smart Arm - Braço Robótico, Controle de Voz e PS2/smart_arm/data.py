import os
import pickle
import random

dataset_path = 'data/dataset.txt'
label_names_path = 'data/label_names.txt'

pickled_dataset='dataset.bin'
pickled_y_train='y_train.bin'

current_dir = os.path.dirname(__file__)

dataset_path =os.path.join(os.path.dirname(__file__),dataset_path)
label_names_path = os.path.join(os.path.dirname(__file__),label_names_path)

pickled_dataset = os.path.join(os.path.dirname(__file__),pickled_dataset)
pickled_y_train = os.path.join(os.path.dirname(__file__),pickled_y_train)


def load_label_names():
    labels =[]
    with open(label_names_path) as f:
        [labels.append(line.replace('\n','').replace('\r','').replace(' ','').lower()) for line in f]
    return labels

label_names=[]
label_names = load_label_names()


def get_label_name(index):
    return label_names[index]

def load():
    if  os.path.exists(pickled_dataset) and os.path.exists(pickled_y_train):
        data_train = pickle.load(open(pickled_dataset,'r+b'))
        y_train = pickle.load(open(pickled_y_train,'r+b'))
        paired_shuffle(data_train,y_train)
        return (data_train,y_train)
    else:
        return(load_fresh())


def load_fresh(path=dataset_path):
    '''
    Load data from dataset and convert target class names to target class numbers. Return (string samples,int targets)
    '''
    data_train=[]
    y_train = []
    #Take special care with files or strings containing accents or characters like 'ç'. Open in binary mode and decode them with byte_array_object.decode('utf-8')
    with open(path,'r+b') as f:
        for line in f:
            line = line.decode('UTF-8').lower()
            x,y =line.replace('\n','').replace('\r','').split(';')
            y = label_names.index(y.replace(' ',''))
            data_train.append(x)
            y_train.append(y)
        paired_shuffle(data_train,y_train)
        return(data_train,y_train)


def save(data_train,y_train):
    data = open(pickled_dataset,'w+b')
    labels = open(pickled_y_train,'w+b')
    pickle.dump(data_train,data)
    pickle.dump(y_train,labels)
    data.close()
    labels.close()
    print('Train data saved')

def paired_shuffle(x,y):
    '''
    In-place paired shuffle of lists x and y. You could use it with features and targets
    '''
    sz = len(x)-1
    for n in range(sz+1):
        rand = random.randint(0,sz)
        x_ = x[rand]
        y_ = y[rand]
        x[rand]=x[n]
        y[rand]=y[n]
        x[n]=x_
        y[n]=y_

def split(data,classes,frac):
    sz = len(data)
    train_data = []
    train_labels = []
    test_data = []
    test_labels=[]
    n = int(sz*frac)
    train_data = data[0:n]
    train_labels = classes[0:n]
    test_data = data[n:sz]
    test_labels = classes[n:sz]
    return (train_data,train_labels,test_data,test_labels)


def clean(file_to_clean,reference_file=dataset_path):
    '''
    Remove duplicate and single character lines from the file_to_clean and lines already found on
    labeled reference dataset
    '''
    print("Cleaning file "+file_to_clean)

    base_data, _ = load_fresh(reference_file)

    output_path, ext = file_to_clean.split('.')
    output_path+= '_clean'
    output_path+='.'+ext

    if not os.path.isabs(file_to_clean):
        file_to_clean = os.path.join(os.path.dirname(__file__),file_to_clean)
        output_path = os.path.join(os.path.dirname(__file__),output_path)

    out = open(output_path,'w')
    input = open(file_to_clean,'r+b')

    lines=[]

    for line in input:
        line = line.decode('UTF-8').lower()
        txt = line.replace('\n','').replace('\r','')
        if (not txt in base_data) and (not line in lines) and len(txt)>1:
            out.write(line)
        lines.append(line)
    input.close()
    out.close()