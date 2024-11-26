from . import prepare_frames_folder, _settings
from .paths import project_root, output_video_path, frames_path
from pathlib import Path
from .world import World
import cv2


def render():
    
    print("====================================")
    print("Vítejte v programu pro renderování videa z textových snímků.")
    volba = input("Pro využití nastavení ze settings.json stiskněte Enter. Pro vygenerování nových defaultních nastavení napište písmeno 'n' a stiskněte Enter: ")
    
    if volba == "n":
        _settings.generate_default_settings()
        
    
    prepare_frames_folder()
    frames_path = get_frames_path()
    
    print("renderuji snímky...")
    
    # add a message every 10% of frames done
    n_frames = len(list(frames_path.iterdir()))
    world = World()
    paths_sorted_by_name = sorted(frames_path.iterdir(), key = lambda x: int(x.stem))
    for i, frame_path in enumerate(paths_sorted_by_name):
        if i % (n_frames // 10) == 0:
            print(f"{i/n_frames * 100:.0f}%")
        world.clear()
        world.load_entities_from_frame(frame_path)
        world.render_frame()    
    
    print("renderování snímků dokončeno. Připravuji video...")
    
    render_video()
    
    print("Hotovo!")
    
    
def get_frames_path() -> Path:
    frames_path = project_root / _settings.get_text_frames_folder_path()
    if frames_path.exists():
        return frames_path
    else:
        raise Exception(f"Cesta k text frames zadaná v settings.json neexistuje: {frames_path}")
    
        
def render_video():
    if output_video_path.exists():
        output_video_path.unlink()
    
    frame_rate = _settings.get_frame_rate()
    first_image = cv2.imread(next(frames_path.iterdir()))
    height, width, _ = first_image.shape
    frame_size = (width, height)
    
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    video_writer = cv2.VideoWriter(output_video_path, fourcc, frame_rate, frame_size)
    
    for frame_path in sorted(frames_path.iterdir(), key = lambda x: int(x.stem)):
        frame = cv2.imread(frame_path)
        video_writer.write(frame)
        
    video_writer.release()