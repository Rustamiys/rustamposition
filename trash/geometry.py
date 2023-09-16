from math import pi, sqrt

class FiguresError(Exception):
    pass

class Figures():
    class Circle():
        def __init__(self, name, radius):
            self.radius = radius
            if self.radius < 0:
                raise FiguresError("arg < 0")
            self.area = pi * self.radius * self.radius


    class Triangle():
        def __init__(self, name, side_1, side_2, side_3):
            self.side_1 = side_1
            self.side_2 = side_2
            self.side_3 = side_3
            # check
            if side_1 <= 0 or side_2 <= 0 or side_3 <= 0:
                raise FiguresError("args <= 0")
            if (side_1 + side_2 <= side_3) or (side_1 + side_3 <= side_2) or (side_2 + side_3 <= side_1):
                raise FiguresError("not triangle")

            __semiper = (side_1 + side_2 + side_3) / 2
            self.area = sqrt(__semiper * (__semiper - side_1) * (__semiper - side_2) * (__semiper - side_3))
        def isRectangle(self):
            if (self.side_1 * self.side_2/2 == self.area) or (self.side_1 * self.side_3/2 == self.area) or (self.side_2 * self.side_3/2 == self.area):
                return True
            else:
                return False
