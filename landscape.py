from graph import *
import random

def rand(H, V):
    return Vector(H * random.random(), H * random.random(), V * random.random())

n = 500

cities = []

i=0
while i < n:
    cities.append(rand(200, 10))
    i+=1


def distance(u, v):
    return (u-v).mag()

roads = []

for i, c in enumerate(cities):
    for j, d in enumerate(cities[:i]):
        if distance(c, d) < 20:
            roads.append(Edge(i, j))


print "\n".join(map(str, cities))
print "\n".join(map(str, roads))

