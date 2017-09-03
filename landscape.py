from graph import *
import random


def rand(A, B, V):
    return Vector((B-A) * random.random() + A, (B-A) * random.random() + A, V * random.random())

def rand_with_height_function(A, B, height_function):
    x, y = random.random(), random.random()
    z = height_function(x, y)
    return Vector((B-A) * x + A, (B-A) * y + A, z)

def random_cities(n, A, B, V):
    cities = []
    i = 0
    while i < n:
        cities.append(rand(A, B, V))
        i+=1
    return cities


def random_cities_with_height_function(n, A, B, height_function):
    cities = []
    i = 0
    while i < n:
        cities.append(rand_with_height_function(A, B, height_function))
        i+=1
    return cities


class RoadMap:
    def __init__(self, cities, roads):
        self.cities = cities
        self.roads = roads

    def __repr__(self):
        return "\n".join(map(str, self.cities)) + "\n" + "\n".join(map(str, self.roads))

    def crosses_roads_so_far(self, a, b):
        '''says whether the edge from a to b would cross
        any of the edges already on the map'''
        for e in self.roads:
            if edges_cross(a, b, self.cities[e.a], self.cities[e.b]):
                return True
        return False

    def smooth_heights(self):
        neighbor_map = {}

        for r in self.roads:
            neighbor_map[r.a] = neighbor_map.get(r.a, []) + [r.b]
            neighbor_map[r.b] = neighbor_map.get(r.b, []) + [r.a]

        for center in neighbor_map:
            neighbors = neighbor_map[center]
            self.cities[center].z = reduce(float.__add__, map(lambda x: self.cities[x].z, neighbors)) / len(neighbors)

    def smooth(self):
        neighbor_map = {}

        for r in self.roads:
            neighbor_map[r.a] = neighbor_map.get(r.a, []) + [r.b]
            neighbor_map[r.b] = neighbor_map.get(r.b, []) + [r.a]

        for center in neighbor_map:
            neighbors = neighbor_map[center]
            self.cities[center] = reduce(Vector.__add__, map(lambda x: self.cities[x], neighbors)) / len(neighbors)


def fantastic_shatter(n):
    '''Random cities, all the same elevation'''
    roadmap = RoadMap(random_cities(n, -100, 100, 0), [])
    for i, c in enumerate(roadmap.cities):
        for j, d in enumerate(roadmap.cities[:i]):
            if not roadmap.crosses_roads_so_far(c, d):
                roadmap.roads.append(Edge(i, j))
    return roadmap


def normalized_shatter(n):
    '''Random cities, all the same elevation'''
    roadmap = RoadMap( random_cities(n, -100, 100, 0), [] )
    for i, c in enumerate(roadmap.cities):
        for j, d in enumerate(roadmap.cities[:i]):
            if distance(c, d) < 20:
                if not roadmap.crosses_roads_so_far(c, d):
                    roadmap.roads.append(Edge(i, j))
    return roadmap


def fractal(x, y, catalog, gen, factor):
    '''Should be obvious what this does'''
    catalog['val'] = catalog.get('val', random.random()-0.5)
    if gen == 0:
        return catalog['val']
    key = str(int(x < 0.5)) + str(int(y < 0.5))
    catalog[key] = catalog.get(key, {})
    return factor * (catalog['val'] + fractal(
            2.0 * math.fmod(x,0.5),
            2.0 * math.fmod(y,0.5), catalog[key], gen-1, factor))


def fractal_landscape_grid(side_n):
    '''side_n^2 cities in a regular grid'''

    cities = []
    catalog = {'val':0}
    for i in range(0, side_n):
        for j in range(0, side_n):
            x = 1.0 * i / side_n
            y = 1.0 * j / side_n
            height = 100.0 * fractal(x, y, catalog, 5, 0.8)
            cities.append(Vector(-100 + 200 * i / side_n, -100 + 200 * j / side_n, height ))

    roads = []
    for j in range(0, side_n):
        for i in range(0, side_n):
            index = j * side_n + i

            if i+1 < side_n:
                roads.append(Edge(index, index+1))
            if index+side_n < side_n * side_n:
                roads.append(Edge(index, index + side_n))

    rm = RoadMap(cities, roads)
    for i in range(0, 10):
        rm.smooth_heights()
    return rm


def fractal_height_random_position(n):
    catalog = {}
    def height_function(x, y):
        return 50 * fractal(x, y, catalog, 5, 0.8)
    roadmap = RoadMap( random_cities_with_height_function(n, -100, 100, height_function), [] )
    for i, c in enumerate(roadmap.cities):
        for j, d in enumerate(roadmap.cities[:i]):
            if distance(c, d) < 40:
                if not roadmap.crosses_roads_so_far(c, d):
                    roadmap.roads.append(Edge(i, j))
    return roadmap


def zero_height_fractal_distribution(n, threshold):
    catalog = {}
    cities = []
    for i in range(0, n):
        x = random.random()
        y = random.random()
        if random.random() - 0.5 < fractal(x, y, catalog, 5, 0.8):
            cities.append( Vector(200 * x - 100, 200 * y - 100, 0) )

    roadmap = RoadMap(cities, [])

    for i, c in enumerate(roadmap.cities):
        for j, d in enumerate(roadmap.cities[:i]):
            if distance(c, d) < threshold:
                if not roadmap.crosses_roads_so_far(c, d):
                    roadmap.roads.append(Edge(i, j))
    return roadmap


# rm = fractal_landscape_grid(100)
# rm = fantastic_shatter(500)
# rm = normalized_shatter(500)
# rm = fractal_height_random_position(500)

rm = zero_height_fractal_distribution(1000, 15.0)

print rm

