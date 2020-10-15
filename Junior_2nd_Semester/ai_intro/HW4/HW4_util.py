#   *** Do not modify the code ***
import pandas as pd
import tqdm
import nltk
import pickle
import gzip
from nltk.corpus import stopwords 
from nltk.tokenize import word_tokenize 
from tqdm import tqdm
nltk.download('punkt')                      
nltk.download('averaged_perceptron_tagger')
nltk.download('stopwords')                  
#   *** Do not modify the code ***

class AI_util:
    def __init__(self):
        return
    def Train_and_Prediction(self, train_data=None):        
        return

    def Split_Train_Test(self, news_data=None):
        import sklearn
        from sklearn.model_selection import train_test_split
        labels = [category for (article_id, tokenized_article, tf_value, category) in news_data]
        news_data = [(article_id, tokenized_article, tf_value) for (article_id, tokenized_article, tf_value, category) in news_data]
        train_data, test_data, train_labels, test_labels = train_test_split(news_data, labels, test_size=0.2, random_state=42)
        return train_data.copy(), test_data.copy(), train_labels.copy(), test_labels.copy()

    def Load_Pickle_Data(self, input_pickle_file_path=None):
        with gzip.open(input_pickle_file_path, mode="rb") as inp_data:
            pickle_data = pickle.load(inp_data)
        return pickle_data.copy()                

    def Load_Data(self, input_csv_file_path=None):
        news_data = pd.read_csv(input_csv_file_path, encoding="UTF-8-sig", engine='python', error_bad_lines=False)
        return_news_data = [(article_id, article_text, article_categroy) \
                            for article_id, article_text, article_categroy \
                            in zip(list(news_data['ArticleId']), list(news_data['Text']), list(news_data['Category']))]
        print("\nComplete data Load : {0}".format(len(return_news_data)))
        return return_news_data.copy()

    #   *** Do not modify the code ***
    def Tokenize(self,input_news_data=None):
        extract_specific_tags =  ['NN', 'NNS', 'NNP', 'NNPS', 'VB', 'VBD', 'VBG', 'VBN', 'VBP', 'VBZ']  # Noun, Verb POS tags
        tokenized_data = list() 
        stop_words = set(stopwords.words('english'))                # Define 'stopwords'
        for one_article in tqdm(input_news_data, desc="Tokenizing... : "):            
            article_id = one_article[0]
            article_text = one_article[1]
            article_categroy = one_article[2]

            article_text = article_text.rstrip("\n")
            article_text = article_text.lower()                       # lower : The -> the / NLP -> nlp
            pos_tokens = nltk.pos_tag(word_tokenize(article_text))   # Tokenize using nltk
            tokenized_data.append((article_id, \
                                    [token[0] for token in pos_tokens if token[1] in extract_specific_tags if not token[0] in stop_words], \
                                    article_categroy))
        return tokenized_data.copy()    

    #   *** Do not modify the code ***
    def Save_Result(self,result=None,predictions=None, test_label=None, std_name=None, std_id=None):
        import sklearn
        from sklearn.metrics import precision_score, recall_score, f1_score,accuracy_score

        path = "./" + str(std_name) + "_" + str(std_id) + ".txt"
        with open(path, mode='w', encoding="UTF-8-sig", errors="ignore") as out:
            max_length = len(result)
            out.write("Total Length : {0}\n".format(max_length))            
            out.write("Accuracy : {0}%\n".format(round(accuracy_score(test_label, predictions)*100)))
            out.write("Precision : {0}%\n".format(round(precision_score(test_label, predictions, average='micro')*100)))
            out.write("Recall : {0}%\n".format(round(recall_score(test_label, predictions, average='micro')*100)))
            out.write("F1 : {0}%\n\n".format(round(f1_score(test_label, predictions, average='micro')*100)))

            for (article_id, category_probability_distribution,predict, label) in result:
                out.write(str(article_id) + "\t")
                for x in category_probability_distribution:
                    out.write(str(x) + "%\t")
                out.write(predict +"\t"+label + "\n")
        print("\nSave the result file : {0}".format(path))

#   *** Do not modify the code ***
