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
        response = requests.get(self.movie_url)
        html = BeautifulSoup(response.content, 'html.parser')
        info = html.find('div', {'class': 'main_detail'})
        self.lst = info.findAll('li')

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
            actor_list.append([x.getText() for x in html.findAll('dd',{'class': 'type_ellipsis'})[1]
                              .findAll('a')])


        print(len(genre_list))
        print(len(director_list))
        print(len(actor_list))
        return genre_list, director_list, actor_list







a=get_url()
b=Movie_Url(a[0])
# b.crawl_movie_name
# b.crawl_movie_rating
# b.crawl_movie_image()
b.crawl_movie_detail()
