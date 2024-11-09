from . import prepare_test_text_frames_folder
from .entity import Entity
from .paths import test_text_frames_path
from math import pi

def generate():
    prepare_test_text_frames_folder()
    n_steps = int(input("Zadejte počet kroků: "))
    e1 = Entity(10, 10, pi/4)
    e2 = Entity(10, 50, 0)
    for i in range(n_steps):
        result = ""
        result += e1.to_str() + "\n"
        result += e2.to_str() + "\n"
        e1.move()
        e2.move()
        
        path = test_text_frames_path / f"{i}.txt"
        with open(path, "w") as file:
            file.write(result)
        