from math import sin, cos, pi, atan2
from . import _settings, coordinate_transformer

class Entity:
    def __init__(self, x, y, phi, type):
        self.x = x
        self.y = y
        self.phi = phi
        self.type = type
        self.prey_size = _settings.get_prey_size()
        self.predator_size = _settings.get_predator_size()
        
    def move(self):
        # for testing of rendering only
        v = 1 # velocity
        self.x += v*cos(self.phi)
        self.y += v*sin(self.phi)
        
    def to_str(self):
        # for testing of rendering only
        x_rounded = round(self.x, 3)
        y_rounded = round(self.y, 3)
        phi_rounded = round(self.phi, 3)
        return f"{x_rounded};{y_rounded};{phi_rounded}"

    @staticmethod
    def from_str(line, type):
        if _settings.get_text_frames_use_phi():
            x, y, phi = map(float, line.split(";"))
        else:
            x, y, vx, vy = map(float, line.split(";"))
            phi = atan2(vy, vx)
        return Entity(x, y, phi, type=type)
    
    
    def get_transformed_points_for_render(self) -> list[tuple[float, float]]:
        size = self.predator_size if self.type == "predator" else self.prey_size
        
        points = []
        
        points.append(coordinate_transformer(self.x, self.y))
        points.append(coordinate_transformer(self.x + size*cos(self.phi + pi + pi/8), self.y + size*sin(self.phi + pi + pi/8)))
        points.append(coordinate_transformer(self.x + size*cos(self.phi + pi - pi/8), self.y + size*sin(self.phi + pi - pi/8)))
        
        return points
        
        
    def get_fill(self) -> str:
        if self.type == "predator":
            return _settings.get_predator_color()
        else:
            return _settings.get_prey_color()
        
        