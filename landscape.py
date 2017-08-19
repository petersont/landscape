from graph import *
import random

def rand(A, B, V):
    return Vector((B-A) * random.random() + A, (B-A) * random.random() + A, V * random.random())

n = 500

cities = []

i=0
while i < n:
    cities.append(rand(-100, 100, 10))
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

