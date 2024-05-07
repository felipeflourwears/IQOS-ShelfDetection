import pygame
import cv2
import numpy as np
import time
import serial

def main():
    # Inicializar pygame
    
    pygame.init()

    # Configuración de la pantalla
    screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
    pygame.mouse.set_visible(False)  # Ocultar el cursor del mouse

    # Cargar los videos
    video1 = cv2.VideoCapture("LoopFinal.mp4")
    video2 = cv2.VideoCapture("IQOS_ILUMA_ONE.mp4")
    video3 = cv2.VideoCapture("IQOS_ILUMA_Mid.mp4")
    current_video = video1

    # Configurar el puerto serial
    serial_port = "COM5"  # Cambia esto al puerto correcto
    baud_rate = 9600  # Asegúrate de que coincida con la configuración del ESP32
    ser = serial.Serial(serial_port, baud_rate)

    while True:
        # Capturar eventos de pygame
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Leer datos del puerto serial
        if ser.in_waiting > 0:
            data = ser.readline().decode('latin-1').rstrip()
            print("Dato recibido:", data)
            if data == "1":
                if current_video != video2:
                    current_video = video2
                    current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)  # Establecer al inicio del video
            elif data == "2":
                if current_video != video3:
                    current_video = video3
                    current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)  # Establecer al inicio del video
        # Mostrar el video actual en pantalla
        ret, frame = current_video.read()
        if not ret:
            current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)
            # Verificar si el video actual es video2 o video3 y si ha terminado de reproducirse
            if current_video in (video2, video3):
                # Cambiar al video en bucle (video1)
                current_video = video1
                current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)

            continue

        frame = cv2.resize(frame, (screen.get_width(), screen.get_height()))
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        pygame_frame = pygame.image.frombuffer(frame.tostring(), frame.shape[1::-1], "RGB")

        screen.blit(pygame_frame, (0, 0))
        pygame.display.flip()

        key = cv2.waitKey(30)
        if key == ord('q'):
            break

    # Liberar recursos y cerrar ventanas
    video1.release()
    video2.release()
    cv2.destroyAllWindows()
    pygame.quit()
    ser.close()

if __name__ == "__main__":
    main()