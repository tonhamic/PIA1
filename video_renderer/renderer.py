from . import prepare_frames_folder
from .paths import project_root, output_video_path, frames_path
from pathlib import Path
from .world import World
import cv2


def render():
    
    prepare_frames_folder()
    frames_path = get_frames_path()
    
    print("renderuji snímky...")
    
    # add a message every 10% of frames done
    n_frames = len(list(frames_path.iterdir()))
    for i, frame in enumerate(frames_path.iterdir()):
        if i % (n_frames // 10) == 0:
            print(f"{i/n_frames * 100:.0f}%")
        world = World.from_file(frame)
        world.render_frame()
    
    print("renderování snímků dokončeno. Připravuji video...")
    
    render_video()
    
    print("Hotovo!")
    
    
def get_frames_path() -> Path:
    frames_path = input("Zadejte cestu ke složce text frames relativně ke složce projektu, nebo nechte prázdné pro testovací text frames: ")
    # je tu shorcut pro testing
    if frames_path == "":
        return project_root / "video_renderer" / "test_text_frames"
    
    # zbytek pro normalni pouziti
    frames_path = project_root / frames_path
    if frames_path.exists():
        return frames_path
    else:
        raise Exception(f"Zadaná cesta neexistuje: {frames_path}")
    
        
def render_video():
    if output_video_path.exists():
        output_video_path.unlink()
    
    frame_rate = 24
    first_image = cv2.imread(next(frames_path.iterdir()))
    height, width, _ = first_image.shape
    frame_size = (width, height)
    
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    video_writer = cv2.VideoWriter(output_video_path, fourcc, frame_rate, frame_size)
    
    for frame_path in sorted(frames_path.iterdir(), key = lambda x: int(x.stem)):
        frame = cv2.imread(frame_path)
        video_writer.write(frame)
        
    video_writer.release()