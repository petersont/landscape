
import math

class Vector:
    def __init__(self, x, y, z):
        self.x = x or 0
        self.y = y or 0
        self.z = z or 0

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y, self.z - other.z)

    def mag(self):
        return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)

    def __repr__(self):
        return "%f, %f, %f"%(self.x, self.y, self.z)


class Edge:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __repr__(self):
        return "%d, %d"%(self.a, self.b)

