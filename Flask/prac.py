from flask import Flask, render_template,url_for,request

app = Flask(__name__)

@app.route('/')
def hello():
	return '<h1>Hello world!</h1>'

@app.route('/user/<name>')
def user(name):
	return render_template('name.html', name=name)


@app.route('/pandas')

# def index():
    # return render_template('index.html')

def make_read_excel():
    import pandas as pd
    # import numpy as np
    #
    # writer = pd.ExcelWriter('static/excel_for_flask.xlsx')
    # df = pd.DataFrame({"col_{}".format(i):list(np.random.randint(0,100,100))for i in range(8)})
    # df.to_excel(writer, 'sheet1')
    # writer.save()
    #
    # df = pd.read_excel('static/excel_for_flask.xlsx')
    df = pd.read_csv('static/movie_df.csv')

    return df.to_html()

@app.route('/submit')
def main_get(num=None):
    return render_template('submit.html',num=num)
@app.route('/calculate',methods=['POST','GET'])
def calculate(num=None):
    if request.method=='POST':
        pass
    elif request.method=='GET':
        temp = request.args.get('num')
        temp = int(temp)

        temp1 = request.args.get('char1')
        return render_template('submit.html',num=temp,char1=temp1)

if __name__ == '__main__':
	app.run(debug=True,threaded=True)