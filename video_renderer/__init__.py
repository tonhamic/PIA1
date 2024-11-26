import shutil
from .paths import frames_path
from .settings import Settings

#imported by other files
_settings = Settings.load()
    
def prepare_frames_folder():
    if frames_path.exists():
        shutil.rmtree(frames_path)
    frames_path.mkdir()
    
def coordinate_transformer(x,y) -> tuple:
    # puts the origin at the lower left corner
    return (x, _settings.get_screen_height() - y)
