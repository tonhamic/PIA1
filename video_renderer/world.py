from .entity import Entity
from pathlib import Path
import matplotlib.pyplot as plt
from math import sin, cos, pi
from .paths import frames_path

class World:
    def __init__(self, id):
        self.entities: list[Entity] = []
        self.id = id
    
    @staticmethod    
    def from_file(path: Path) -> "World":
        w = World(id=int(path.stem))
        with open(path) as file:
            file = file.read().split("\n")
            for line in file:
                if line == "":
                    continue
                entity = Entity.from_str(line)
                w.entities.append(entity)
        return w
    
    def render_frame(self):
        fig, ax = plt.subplots(figsize=(5, 5))
        ax.set_xlim(0, 500)
        ax.set_ylim(0, 500)

        # background
        fig.patch.set_facecolor('#DDDCAB')
        
        a = 5
        for e in self.entities:
            points = [
                [e.x, e.y], 
                [e.x + a*cos(e.phi + pi + pi/8), e.y + a*sin(e.phi + pi + pi/8)], 
                [e.x + a*cos(e.phi + pi - pi/8), e.y + a*sin(e.phi + pi - pi/8)]
            ]
            triangle = plt.Polygon(points, closed=True, color='blue', alpha=0.8)
            ax.add_patch(triangle)

        ax.axis('off')
        file_path = frames_path / f"{self.id}.png"
        plt.savefig(file_path, bbox_inches='tight', facecolor=fig.get_facecolor(), dpi=200)
        plt.close(fig)

