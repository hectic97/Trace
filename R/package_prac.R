set.seed(2)
x = runif(10,0,11)
x
y = 2+3*x+rnorm(10,0,0.2)
y
dfrm<-data.frame(x,y)
dfrm
lm(y~x,data=dfrm)

u<-runif(10,0,11)
v<-runif(10,0,20)
w<-runif(10,1,30)
y = 3+0.1*u+2*v-3*w*rnorm(10,0,0.1)
dfrm1<-data.frame(y,u,v,w)
dfrm1
m<-lm(y~u+v+w,data=dfrm1)
summary(m)

data(cars)
m<-lm(dist~speed,cars)
summary(m)
par(mfrow=c(2,2))
plot(m)

x1<-c(7,1,11,11,7,11,3,1,2,21,1,11,10)
x2<-runif(13,1,11)
x3<-x2+1
x4<-runif(13,7,11)
y<-c(3*x1+4*x2+2*x3+0.5*x4+113)
df<-data.frame(x1,x2,x3,x4,y)
head(df)
m<-lm(y~x1+x2+x3+x4,data=df)
m

loc<-cmdscale(eurodist)
loc
plot(loc[,1],loc[,2],type='n',main='eurodist')
text(loc[,1],loc[,2],rownames(loc),cex=.8,col="red")
abline(v=0,h=0)

prcomp(data(USArrests),scale=TRUE)
