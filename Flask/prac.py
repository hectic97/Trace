from flask import Flask, render_template,url_for,request,redirect

app = Flask(__name__)

chosen_movies=[]

@app.route('/fmr/info')
def info():
	return render_template('info.html')

@app.route('/')
def home():
	return render_template('home.html')


# @app.route('/pandas')

# def index():
    # return render_template('index.html')
#
# def make_read_excel():
#     import pandas as pd
#     # import numpy as np
#     #
#     # writer = pd.ExcelWriter('static/excel_for_flask.xlsx')
#     # df = pd.DataFrame({"col_{}".format(i):list(np.random.randint(0,100,100))for i in range(8)})
#     # df.to_excel(writer, 'sheet1')
#     # writer.save()
#     #
#     # df = pd.read_excel('static/excel_for_flask.xlsx')
#     df = pd.read_csv('static/movie_df.csv')
#
#     return df.to_html()

# @app.route('/submit')
# def main_get(num=None):
#     return render_template('submit.html',num=num)
# @app.route('/calculate',methods=['POST','GET'])
# def calculate(num=None):
#     if request.method=='POST':
#         pass
#     elif request.method=='GET':
#         temp = request.args.get('num')
#         temp = int(temp)
#
#         temp1 = request.args.get('char1')
#         return render_template('submit.html',num=temp,char1=temp1)

@app.route('/fmr', methods=['POST','GET'])
def select():
    if request.method == 'POST':
        print(request.form.getlist('chosen_movie'))
        global chosen_movies
        chosen_movies=request.form.getlist('chosen_movie')
        print(chosen_movies)
        return redirect('/fmr/result')
    return render_template('select.html')

@app.route('/fmr/result')
def results():
    import pandas as pd
    import numpy as np
    a = pd.read_csv('static/txt_info.txt',header=None)
    d = a.iloc[chosen_movies].values
    e = (' ').join(d.squeeze())
    print(chosen_movies)
    from sklearn.feature_extraction.text import CountVectorizer
    cv = CountVectorizer()
    a.loc[850]=e
    cv_a = cv.fit_transform(a.values.squeeze())
    from sklearn.metrics.pairwise import cosine_similarity
    cs = cosine_similarity(cv_a,cv_a)
    f = pd.read_csv('static/movie_df.csv')
    # new_df = f.loc[np.argsort(cs[850])[::-1][len(chosen_movies)+1:len(chosen_movies)+15]].sort_values(by='movie_rating',
    #                                                                                                   ascending=False)[:10]
    indexes=np.argsort(cs[850])[::-1]
    int_chosen_movie = list(map(int, chosen_movies))
    for x in int_chosen_movie:
        indexes=np.delete(indexes, np.where(indexes==x))
    indexes=np.delete(indexes, np.where(indexes==850))
    new_df=f.loc[indexes[:15]].sort_values(by='movie_rating',ascending=False)[:10]
    new_df=new_df.drop(['Unnamed: 0','movie_genre','movie_director','movie_actor'],axis=1)
    new_df = new_df.reset_index(drop=True)
    new_df.index = new_df.index+1
    new_df = new_df.rename(columns={'movie_name': 'MOVIE', 'movie_rating': 'Rating', 'movie_genre_split': 'Genre',
                          'movie_director_split': 'Director', 'movie_actor_split': 'Cast'})

    return'<h1>&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;###### TOP 10 MOVIES FOR YOU #####</h1>'+new_df.to_html(justify='center')+"<a href='/fmr'><br>Go Back</a>"


if __name__ == '__main__':
	app.run(debug=True,threaded=True)

"""<div style = "font:italic bold 1.1em/1em 'Georgia',serif;text-align:center;font-size:26px;color:#FFFFFF">
<h1> Movie recommendation system </h1>
</div>"""