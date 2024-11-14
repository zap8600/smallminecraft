import json

with open('textures.json') as json_data:
    d = json.load(json_data)
    json_data.close()
    for i in range(len(d)):
        for i in range(8):
            print(d[0][0 + i], d[0][1 + i], d[0][2 + i], d[0][3 + i], d[0][4 + i], d[0][5 + i], d[0][6 + i], d[0][7 + i])