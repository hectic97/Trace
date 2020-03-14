from flask  import Flask,render_template,request,url_for

app = Flask(__name__,static_url_path='/static')

@app.route('/')