# -*- coding: utf-8 -*-
"""Untitled4.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1E2OzI1erDbBz6vJqb_mstRdY5GVvoVh-
"""

#   *** Do not import any library except already imported libraries ***
import tqdm
import math
from tqdm import tqdm,trange
from HW4_util import AI_util
#   *** Do not import any library except already imported libraries ***

class Naive_Bayes(AI_util):
    def Train_and_Prediction(self, train_data=None, test_data=None, train_labels=None, test_labels=None, vocab=None):
        return_data_1 = []
        return_data_2 = []
        prob = dict()
        label_list = list(set(train_labels+test_labels))
        for tl in train_labels:
            if tl not in prob:
                prob[tl] = 0
            prob[tl] += 1
        for lb in label_list:
            prob[lb] /= len(train_labels)
            trx=[]
            feature_prob=[]
            for td,tl in zip(train_data,train_labels):
                if lb==tl:
                    trx.append(td[2])
            sum_all = len(trx)+2
            for i,t in enumerate(trx[0]):
                temp=[x[i] for x in trx]
                cnt = 0
                for el in temp:
                    if el > 0:
                        cnt += 1
                feature_prob.append((cnt+1)/(sum_all))
            prob['feature|'+lb] = feature_prob
        for td,tl in tqdm(zip(test_data,test_labels)):
            cate_prob={}
            for lb in label_list:
                cate_prob[lb]=math.log(prob[lb],2)+sum([y*math.log(x,2) for x,y in zip(prob['feature|'+lb],td[2])])
            pred_label = sorted(cate_prob.items(),key=(lambda x:x[1]),reverse=True)[0][0]
            log_transformed_denominator = (sum(cate_prob.values()))/4
            for key in cate_prob:
                cate_prob[key] -= log_transformed_denominator
            all = sum(cate_prob.values())
            for key in cate_prob:
                cate_prob[key] = round(cate_prob[key]/all*100,2)
            return_data_1.append((td[0],cate_prob.values(),pred_label,tl))
            return_data_2.append(pred_label)
        return return_data_1,return_data_2

if __name__ == "__main__":
    #   *** Do not modify the code below ***
    naive_bayes = Naive_Bayes()
    news_data = naive_bayes.Load_Pickle_Data(input_pickle_file_path="HW4_BBC_Data.pickle")
    vocab = naive_bayes.Load_Pickle_Data(input_pickle_file_path="HW4_Vocab.pickle")
    train_data, test_data, train_labels, test_labels = naive_bayes.Split_Train_Test(news_data=news_data)

    result, predictions = naive_bayes.Train_and_Prediction(train_data=train_data, test_data=test_data, train_labels=train_labels, test_labels=test_labels, vocab=vocab)
    naive_bayes.Save_Result(result=result, predictions=predictions, test_label=test_labels, std_name="StudentName", std_id ="StudentID")
    #   *** Do not modify the code above ***

