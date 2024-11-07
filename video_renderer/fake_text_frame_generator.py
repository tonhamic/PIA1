from . import prepare_environment
from .entity import Entity
from .paths import fake_text_frames_path
from math import pi

def generate():
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
        