from . import prepare_frames_folder
from .paths import project_root
from pathlib import Path
from .world import World

def get_frames_path() -> Path:
    frames_path = input("zadejte cestu ke složce text frames relativně ke složce projektu: ")
    # je tu shorcut pro testing
    if frames_path == "":
        return project_root / "video_renderer" / "test_text_frames"
    
    # zbytek pro normalni pouziti
    frames_path = project_root / frames_path
    if frames_path.exists():
        return frames_path
    else:
        raise Exception(f"Zadaná cesta neexistuje: {frames_path}")
    

def render():
    
    prepare_frames_folder()
    frames_path = get_frames_path()
    
    print("rendering...")
    for text_frame in sorted(frames_path.iterdir(), key = lambda x: int(x.stem)):
        world = World.from_file(text_frame)
        world.render_frame()
    
    print("rendering individual frames complete. preparing video...")
    
    
        