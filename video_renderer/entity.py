import math

class Entity:
    def __init__(self, x, y, phi):
        self.x = x
        self.y = y
        self.phi = phi
        
    def move(self):
        v = 1 # velocity
        self.x += v*math.cos(self.phi)
        self.y += v*math.sin(self.phi)
        
    def to_str(self):
        x_rounded = round(self.x, 3)
        y_rounded = round(self.y, 3)
        phi_rounded = round(self.phi, 3)
        return f"{x_rounded};{y_rounded};{phi_rounded}"

    @staticmethod
    def from_str(line, uses_vxvy):
        if uses_vxvy:
            x, y, vx, vy = map(float, line.split(";"))
            phi = math.atan2(vy, vx)
        else:
            x, y, phi = map(float, line.split(";"))
        return Entity(x, y, phi)