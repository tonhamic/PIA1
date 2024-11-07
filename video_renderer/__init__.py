import shutil
from .entity import Entity
from math import pi
from .paths import test_text_frames_path, frames_path


def prepare_test_text_frames_folder():
    if test_text_frames_path.exists():
        shutil.rmtree(test_text_frames_path)
    test_text_frames_path.mkdir()
    
def prepare_frames_folder():
    if frames_path.exists():
        shutil.rmtree(frames_path)
    frames_path.mkdir()
