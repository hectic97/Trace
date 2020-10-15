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
        for tl in label_list:
            prob[tl] /= len(train_labels)
        for td,tl in zip(test_data,test_labels):
            trx = []
            cate_prob=dict()
            for label in label_list:
                for i,l in enumerate(train_labels):
                    if l==label:
                        trx.append(train_data[i][2])
                temp = []
                for i,feature in enumerate([t+1 for t in td[2]]):
                    #feature_tr.count(feature)+1)
                    feature_tr = [x[i] for x in trx]
                    temp.append(math.log((feature+1)/len(feature_tr),2))
                    # print(temp)
                    # print(feature)
                    # print(feature_tr.count(feature),len(feature_tr),len(set(feature_tr)))
                    # exit(0)
                print(temp)
                mul = 0
                # print(len(temp))
                for x in temp:
                    mul += x
                # print(mul)
                cate_prob[label] = mul + math.log(prob[label],2)
                # exit(0)
            print(cate_prob)
            print()
            exit(0)

            



        """
            *** You should implement this function with raw code ***
            *** When you code, you have to erase this comment ***
            
            (input) 'train_data/test_data' data type : ('list')
            (input) 'train_data/test_data' data format :  [(article id, tokens, tf_value)]
            (input) 'train_data/test_data' data example :  [(857, ['eviction', ... , 'night'], [2, 0, 0, ..., 0]), ..., (154, ['business', ..., 'rise'], [4, 0, 0, ..., 0]), ...]

            (input) 'train_labels/test_labels' data type : ('list')
            (input) 'train_labels/test_labels' data format :  [category]
            (input) 'train_labels/test_labels' data example :  ['business', 'business', 'tech', ..., 'entertainment']

            (input) 'vocab' data type : ('list')
            (input) 'vocab' data type : [tokens]
            (input) 'vocab' data type : ['info', '1970s', ..., 'travel']
            ========
            (output) 'return data1' type : ('list')
            (output) 'return data1' format : [(article id, Category probability distribution, prediction of model, true label)]            
            (output) 'return data1' example : [(2160, [7.35, 35.11, 12.93, 26.61, 18], 'business', 'entertainment'), ...]            

            (output) 'return data2' type : ('list')
            (output) 'return data2' format : [prediction of model]            
            (output) 'return data2' example :  ['business', 'business', 'politics', ..., 'entertainment']            
        """

if __name__ == "__main__":
    #   *** Do not modify the code below ***
    naive_bayes = Naive_Bayes()
    news_data = naive_bayes.Load_Pickle_Data(input_pickle_file_path="HW4_BBC_Data.pickle")
    vocab = naive_bayes.Load_Pickle_Data(input_pickle_file_path="HW4_Vocab.pickle")
    train_data, test_data, train_labels, test_labels = naive_bayes.Split_Train_Test(news_data=news_data)

    result, predictions = naive_bayes.Train_and_Prediction(train_data=train_data, test_data=test_data, train_labels=train_labels, test_labels=test_labels, vocab=vocab)
    naive_bayes.Save_Result(result=result, predictions=predictions, test_label=test_labels, std_name="StudentName", std_id ="StudentID")
    #   *** Do not modify the code above ***
