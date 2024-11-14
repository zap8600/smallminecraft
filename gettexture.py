import json

with open('textures.json') as json_data:
    global d
    d = json.load(json_data)
    json_data.close()
    for j in range(len(d)):
        for i in range(8):
            print(d[j][0 + (i * 8)], d[j][1 + (i * 8)], d[j][2 + (i * 8)], d[j][3 + (i * 8)], d[j][4 + (i * 8)], d[j][5 + (i * 8)], d[j][6 + (i * 8)], d[j][7 + (i * 8)])

i = 0
j = 0x
print(d[j][0 + (i * 8)], d[j][1 + (i * 8)], d[j][2 + (i * 8)], d[j][3 + (i * 8)], d[j][4 + (i * 8)], d[j][5 + (i * 8)], d[j][6 + (i * 8)], d[j][7 + (i * 8)])