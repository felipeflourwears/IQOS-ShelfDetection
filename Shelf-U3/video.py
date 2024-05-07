import pygame
from moviepy.editor import VideoFileClip
import numpy as np

def main():
    pygame.init()
    screen = pygame.display.set_mode((1920, 1080))
    pygame.display.set_caption("Reproducción de video con Pygame")

    # Carga el video
    clip = VideoFileClip("loop.mp4")
    clipoption1 = VideoFileClip("video1.mp4")
    clipoption2 = VideoFileClip("video2.mp4")

    # Bucle principal
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Reproduce el video
        frame_time = pygame.time.get_ticks() / 1000
        frame = clip.get_frame(frame_time % clip.duration)
        frame_surface = pygame.surfarray.make_surface(np.transpose(frame, (1, 0, 2)))
        screen.blit(frame_surface, (0, 0))
        pygame.display.flip()

    pygame.quit()

if __name__ == "__main__":
    main()
