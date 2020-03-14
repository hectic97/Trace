from flask import Flask, render_template

app = Flask(__name__, static_url_path='/static')

@app.route('/pandas')

# def index():
    # return render_template('index.html')

def make_read_excel():
    import pandas as pd
    import numpy as np

    writer = pd.ExcelWriter('static/excel_for_flask.xlsx')
    df = pd.DataFrame({"col_{}".format(i):list(np.random.randint(0,100,100))for i in range(8)})
    df.to_excel(writer, 'sheet1')
    writer.save()

    df = pd.read_excel('static/excel_for_flask.xlsx')
    return df.to_html()

if __name__ == "__main__":
    app.run(debug=True, threaded = True)