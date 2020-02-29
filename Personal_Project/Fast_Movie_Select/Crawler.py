import requests
from bs4 import BeautifulSoup
from urllib import request
import numpy as np
import pandas as pd


def get_url():
    url_list = []
    for i in range(2004, 2021):
        url_list.append('https://movie.daum.net/boxoffice/yearly?year=' + str(i))
    return url_list


class Movie_Url:
    def __init__(self, movie_url):
        self.movie_url = movie_url
        self.lst = self.navigate_url()
        self.name_list = self.crawl_movie_name()
        self.rating_list = self.crawl_movie_rating()
        self.genre_list, self.director_list, self.actor_list = self.crawl_movie_detail()

    def navigate_url(self):
        response = requests.get(self.movie_url)
        html = BeautifulSoup(response.content, 'html.parser')
        info = html.find('div', {'class': 'main_detail'})
        return info.findAll('li')

    def crawl_movie_name(self):
        name_list = []
        for lt in self.lst:
            name = lt.find('strong').getText()
            name_list.append(name)
        return name_list

    def crawl_movie_rating(self):
        rating_list=[]
        for lt in self.lst:
            rating = lt.find('em').getText()
            rating_list.append(rating)
        return rating_list

    def crawl_movie_image(self):
        for i, lt in enumerate(self.lst):
            img = str(lt.find('img'))
            img_url = img[img.find('http'):img.find('onload')-2]

            request.urlretrieve(img_url, "./image/"+str(self.movie_url[-4:])+str(i+1)+".png")
        print('Image Downloaded')

    def crawl_movie_detail(self):
        base_url = 'https://movie.daum.net'
        genre_list = []
        director_list = []
        actor_list = []

        for lt in self.lst:
            stlt = str(lt)
            stlt_2 = stlt[stlt.find('href=')+6:]
            stlt_3 = stlt_2[:stlt_2.find('>')-1]

            new_url = base_url+str(stlt_3)
            response = requests.get(new_url)
            html = BeautifulSoup(response.content, 'html.parser')
            new_info = html.find('div', {'class': 'movie_summary'})
            genre_list.append(new_info.findAll('dd')[0].getText())
            director_list.append(html.find('dd', {'class': 'type_ellipsis'}).find('a').getText())
            try:
                actor_list.append([x.getText() for x in html.findAll('dd',{'class': 'type_ellipsis'})[1]
                              .findAll('a')])
            except IndexError:
                actor_list.append('X')

        genre_list = [genre.split('/') for genre in genre_list]

        return genre_list, director_list, actor_list

    def make_movie_df(self):
        df_movie = pd.DataFrame()
        df_movie['movie_name'] = self.name_list
        df_movie['movie_rating'] = self.rating_list
        df_movie['movie_genre'] = self.genre_list
        df_movie['movie_director'] = self.director_list
        df_movie['movie_actor'] = self.actor_list

        return df_movie

def object_column_preprocess(df):
    df = df.reset_index(drop=True)
    df['movie_genre_split'] = df['movie_genre'].apply(lambda x: (' ').join(x))
    df['movie_director_split'] = df['movie_director'].apply(lambda x: x.replace(' ', ''))
    df['movie_actor_split'] = df['movie_actor'].apply(
        lambda x: (' ').join([ac.replace(' ', '') for ac in x]))

    return df


url_list = get_url()
for i, year_url in enumerate(url_list):
    movie = Movie_Url(year_url)
    # movie.crawl_movie_image()
    if i == 0:
        movie_df = movie.make_movie_df()
    else:
        movie_df = pd.concat([movie_df, movie.make_movie_df()], axis=0)

    print(i)

movie_df = object_column_preprocess(movie_df)
# movie_2004 = Movie_Url(url_list[0])
# df_2004 = movie_2004.make_movie_df()
# print(df_2004)
