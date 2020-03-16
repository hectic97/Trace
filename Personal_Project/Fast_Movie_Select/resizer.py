from PIL import Image
for j in range(2004,2021):
    for i in range(50):
        im = Image.open("./image/"+str(j)+str(i+1)+'.png').convert('RGB')
        im=im.resize((280,400))
        im.save('./image/'+str(j)+str(i+1)+'.jpg',quality=60)
