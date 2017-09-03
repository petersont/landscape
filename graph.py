
import math

class Vector:
    def __init__(self, x, y, z):
        self.x = float(x or 0.0)
        self.y = float(y or 0.0)
        self.z = float(z or 0.0)

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y, self.z - other.z)

    def __div__(self, k):
        return Vector(self.x/k, self.y/k, self.z/k)

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


epsilon = 0.001

def edges_cross(a, b, c, d):
    ''' Takes four 2-dimensional points a, b, c, d.
        Returns true if the line segment a-b crosses the linesegment c-d '''
    A = a.x - b.x
    B = d.x - c.x
    C = a.y - b.y
    D = d.y - c.y

    X = d.x - b.x
    Y = d.y - b.y

    det = A * D - B * C

    if det == 0:
        return False

    u = (D * X - B * Y) / det
    v = (A * Y - C * X) / det

    return u > epsilon and u < 1.0-epsilon and v > epsilon and v < 1.0-epsilon


def distance(u, v):
    return (u-v).mag()
