import serial
import pygame
from moviepy.editor import VideoFileClip
import numpy as np
import threading

# Configura el puerto serial
puerto_serial = serial.Serial('COM7', 9600)  # Reemplaza 'COM7' con tu puerto serial

def leer_serial():
    while True:
        sharp = puerto_serial.readline().decode().strip()
        print("Recibido:", sharp)
        # Aquí puedes agregar lógica adicional para manejar los datos recibidos del puerto serial

def main():
    pygame.init()
    screen = pygame.display.set_mode((1920, 1080))
    pygame.display.set_caption("Reproducción de video con Pygame")

    # Carga el video
    clip = VideoFileClip("loop.mp4")
    clipoption1 = VideoFileClip("video1.mp4")
    clipoption2 = VideoFileClip("video2.mp4")

    # Inicia el hilo para leer el puerto serial
    serial_thread = threading.Thread(target=leer_serial)
    serial_thread.daemon = True
    serial_thread.start()

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
