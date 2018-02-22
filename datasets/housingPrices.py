import requests as r
from bs4 import BeautifulSoup

priceList = list()
areaList = list()

for i in range(1, 283):
    if i == 1:
        url = "https://www.99acres.com/rent-property-in-chennai-ffid"
    else:
        url = "https://www.99acres.com/rent-property-in-chennai-ffid-page-"+ str(i)
    source = r.get(url)
    soup = BeautifulSoup(source.content, 'lxml')
    p = soup.find_all(itemprop="price")
    d = soup.find_all(itemprop="description")
    for price in p:
        priceList.append(price.get_text())
    for entry in d:
        temp = entry.b
        areaList.append(temp.get_text())
    print("Iteration: ", i)


print(len(priceList))
print(len(areaList))

with open('dataset2.csv', 'w') as output:
    for i in range(0, len(areaList)):
        output.write(str(areaList[i]) + ',' + str(priceList[i]) + '\n')

