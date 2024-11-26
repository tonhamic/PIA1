from .entity import Entity
from pathlib import Path
from .paths import frames_path
from . import _settings
from PIL import Image, ImageDraw


class World:
    def __init__(self):
        self.entities: list[Entity] = []
        self.id = None
        self.height = _settings.get_screen_height()
        self.width = _settings.get_screen_width()
        self.image = Image.new("RGB", (self.width, self.height), _settings.get_background_color())
        self.draw = ImageDraw.Draw(self.image)
        
    def load_entities_from_frame(self, text_frame_path: Path) -> None:
        self.entities = []
        # struktura souboru je takova, ze blok preys a predators je oddelen prazdnou linkou
        
        with open(text_frame_path) as file:
            file = file.read().split("\n")
            blank_line_passed = False
            
            for line in file:
                if line.strip() == "":
                    blank_line_passed = True
                    continue
                type = "predator" if blank_line_passed else "prey"
                entity = Entity.from_str(line, type=type)
                self.entities.append(entity)
                
        self.id = text_frame_path.stem
    
    
    def clear(self):
        self.draw.rectangle([0, 0, self.width, self.height], fill=_settings.get_background_color())
        self.entities = []
        

    def render_frame(self):
        pass
        for e in self.entities:
            self.draw.polygon(e.get_transformed_points_for_render(), fill=e.get_fill())
        file_path = frames_path / f"{self.id}.png"
        self.image.save(file_path, "PNG")