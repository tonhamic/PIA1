from .paths import settings_path
import json

class Settings:
    def __init__(self):
        if not settings_path.exists():
            self.generate_default_settings()
        self._dict = None
        
    def generate_default_settings(self) -> "Settings":
        settings = {
            "screen_width": 1270,
            "screen_height": 720,
            "frame_rate": 30,
            "text_frames_use_phi": False,
            "prey_size": 15,
            "predator_size": 25,
            "predator_color": "red",
            "prey_color": "blue",
            "background_color": "white",
            "text_frames_folder_path": "simulation_data"
        }
        with open(settings_path, "w") as file:
            json.dump(settings, file, indent=4)
        
        self._dict = settings
        return self
        
    @staticmethod
    def load() -> "Settings":
        s = Settings()
        with open(settings_path) as file:
            s._dict = json.load(file)
        return s
        
    def get_frame_rate(self) -> int:
        return self._dict["frame_rate"]
    
    def get_screen_width(self) -> int:
        return self._dict["screen_width"]

    def get_screen_height(self) -> int:
        return self._dict["screen_height"]
    
    def get_text_frames_use_phi(self) -> bool:
        return self._dict["text_frames_use_phi"]
    
    def get_prey_size(self) -> int:
        return self._dict["prey_size"]
    
    def get_predator_size(self) -> int:
        return self._dict["predator_size"]

    def get_text_frames_folder_path(self) -> str:
        return self._dict["text_frames_folder_path"]

    def get_background_color(self) -> str:
        return self._dict["background_color"]
    
    def get_predator_color(self) -> str:
        return self._dict["predator_color"]
    
    def get_prey_color(self) -> str:
        return self._dict["prey_color"]
    