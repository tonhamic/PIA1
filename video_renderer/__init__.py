from pathlib import Path
import shutil
from .entity import Entity
from math import pi

p = Path.cwd()
fake_text_frames_path = p / "video_renderer" / "fake_text_frames"


def prepare_environment():
    if fake_text_frames_path.exists():
        shutil.rmtree(fake_text_frames_path)
    fake_text_frames_path.mkdir()
    

def generator():
    n_steps = 100
    prepare_environment()
    e1 = Entity(10, 10, pi/4)
    e2 = Entity(10, 50, 0)
    for i in range(n_steps):
        result = ""
        result += e1.to_txt() + "\n"
        result += e2.to_txt() + "\n"
        e1.move()
        e2.move()
        
        path = fake_text_frames_path / f"{i}.txt"
        with open(path, "w") as file:
            file.write(result)
        
    
def render():
    print("rendering")