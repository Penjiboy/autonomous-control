#!/usr/bin/python3

import math


class Vector:
    x = 0
    y = 0

    def set_from_polar(self, r, rho):
        self.x = r * math.cos(math.radians(rho))
        self.y = r * math.sin(math.radians(rho))

    def distance_to(self, other):
        tmp = other - self
        return math.hypot(tmp.x, tmp.y)

    def angle_to(self, other):
        return math.atan2(other.x, other.y) - math.atan2(self.x, self.y)

    def set_coords(self, coords):
        self.x = coords[0]
        self.y = coords[1]

    def get_coords(self):
        return (self.x, self.y)

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y)

    def __str__(self):
        return str(self.x) + ", " + str(self.y)
