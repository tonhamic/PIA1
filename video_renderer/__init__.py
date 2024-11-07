import shutil
from .entity import Entity
from math import pi
from .paths import fake_text_frames_path


def prepare_environment():
    if fake_text_frames_path.exists():
        shutil.rmtree(fake_text_frames_path)
    fake_text_frames_path.mkdir()
