import shutil
import json
from .paths import test_text_frames_path, frames_path, settings_path
from .settings import Settings

#imported by other files
_settings = Settings.load()
    
def prepare_test_text_frames_folder():
    if test_text_frames_path.exists():
        shutil.rmtree(test_text_frames_path)
    test_text_frames_path.mkdir()
    
def prepare_frames_folder():
    if frames_path.exists():
        shutil.rmtree(frames_path)
    frames_path.mkdir()
