from os import error
import requests
import gzip
import json
import zlib
from io import BytesIO
import uuid
from random import choice
import time
import math


def read_and_parse_signal(path: str):
    y = 100 + (1.0/20.0) * 1 * math.sqrt(1)
    column = 0
    i = 0
    g = []
    with open(path) as g1_f:
        f = g1_f.readlines()
        for l in f:
            g.append(float(l.replace(",", ".")) * y)
            if i % 795 == 0:
                column += 1
                y = 100 + (1.0/20.0) * column * math.sqrt(column)
            i += 1
    return g


g1 = read_and_parse_signal("./g-1.txt")
g3 = read_and_parse_signal("./g-3.txt")
a1 = read_and_parse_signal("./a-1.txt")

data = {
    'algorithm': "fista",
    'datetime': "123",
}

data["signal"] = g1


request_cache = []

for i in range(25):
    data["token"] = str(uuid.uuid4())

    data_choice = choice([1, 2, 3])
    if data_choice == 1:
        data["signal"] = g1
    elif data_choice == 2:
        data["signal"] = g3
    else:
        data["signal"] = a1

    if(choice([1, 2]) == 1):
        data["algorithm"] = "fista"
    else:
        data["algorithm"] = "ccgn"

    print(requests.post("http://localhost:8080/post_new_signal", json=data))

    data["signal"] = []
    request_cache.append(data.copy())


for request_data in request_cache:
    r = requests.post(
        "http://localhost:8080/status_feedback", json=request_data)
    print(r.json())
    status = r.json()
    while status["status"] != "Processo completo.":
        time.sleep(1)
        r = requests.post(
            "http://localhost:8080/status_feedback", json=request_data)
        js = r.json()
        print(js)
        status = js

    r = requests.post("http://localhost:8080/get_image", json=request_data)

    try:
        r = bytes(r.json()["bytes"])

        with open(request_data["token"] + ".png", "wb+") as img:
            img.write(r)
    except:
        print("ERROR, DATA: " + r.json())
        raise
