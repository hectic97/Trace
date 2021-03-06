# -*- coding: utf-8 -*-
"""A2_compare_algorithms.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1PzaY1kItg6wFzHXjRDDPTX5H5aK5oEu7
"""

from sklearn.datasets import load_digits
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

d=load_digits()

data = d.data
image = d.images
target = d.target

plt.imshow(image[0],cmap='binary')

image.shape

data

# Preprocessing

data.shape

np.unique(target)

from sklearn.model_selection import train_test_split
x_train,x_test,y_train,y_test = train_test_split(data,target,stratify=target,test_size=.2)

from sklearn.pipeline import Pipeline
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.linear_model import Logisti,cRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score

pipe=Pipeline([('scaler',StandardScaler()),('clf',KNeighborsClassifier())],memory='cache_folder')
param_grid=[
            {'clf':[KNeighborsClassifier()],'scaler':[StandardScaler(),MinMaxScaler(),None],
             'clf__n_neighbors':[3,5,7,9,11]},
            {'clf':[DecisionTreeClassifier(),RandomForestClassifier()],'clf__max_depth':[3,5,7,None],'clf__min_samples_leaf':[1,3,5,10]},
            {'clf':[LogisticRegression()],'scaler':[StandardScaler(),MinMaxScaler(),None],'clf__C':[0.01,1,100],'clf__max_iter':[10000],
             'clf__multi_class':['ovr'],'clf__penalty':['l2']},
            {'clf':[SVC()],'scaler':[StandardScaler(),MinMaxScaler(),None],'clf__kernel':['rbf'],'clf__C':[0.01,1,100],
             'clf__gamma':[0.01,0.1,1]},
]

from sklearn.model_selection import GridSearchCV
grid = GridSearchCV(pipe,param_grid,cv=5,verbose=1,n_jobs=-1)
grid.fit(x_train,y_train)

grid.best_params_

grid.best_score_

grid.score(x_test,y_test)

pd.set_option('display.max_colwidth', -1)

pd.DataFrame(grid.cv_results_)[['params','mean_test_score']].sort_values('mean_test_score',ascending=False)[:5]