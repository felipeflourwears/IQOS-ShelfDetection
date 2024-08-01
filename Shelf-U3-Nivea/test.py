import pygame
import cv2
import os
import serial

def main():
    # Inicializar pygame
    pygame.init()

    # Configuración de la pantalla
    screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
    pygame.mouse.set_visible(False)  # Ocultar el cursor del mouse

    # Definir los nombres de los archivos de video
    video_files = ["1.mp4", "2.mp4", "3.mp4", "4.mp4"]
    videos = []

    # Verificar si los archivos de video existen y se pueden abrir
    for file in video_files:
        if os.path.isfile(file):
            video = cv2.VideoCapture(file)
            if video.isOpened():
                videos.append(video)
            else:
                print(f"Error al abrir el video {file}")
                return
        else:
            print(f"Archivo no encontrado: {file}")
            return

    current_video = videos[0]

    # Configurar el puerto serial
    serial_port = "COM5"  # Cambia esto al puerto correcto
    baud_rate = 9600  # Asegúrate de que coincida con la configuración del ESP32
    ser = serial.Serial(serial_port, baud_rate)

    running = True

    while running:
        # Capturar eventos de pygame
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Leer datos del puerto serial
        if ser.in_waiting > 0:
            data = ser.readline().decode('latin-1').rstrip()
            print("Dato recibido:", data)
            if data == "1":
                if current_video != videos[1]:
                    current_video = videos[1]
                    current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)  # Establecer al inicio del video
            elif data == "2":
                if current_video != videos[2]:
                    current_video = videos[2]
                    current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)  # Establecer al inicio del video
            elif data == "3":
                if current_video != videos[3]:
                    current_video = videos[3]
                    current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)  # Establecer al inicio del video

        # Mostrar el video actual en pantalla
        ret, frame = current_video.read()
        if not ret:
            print("Fin del video o error al leer el frame.")
            current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)
            # Verificar si el video actual es video2, video3 o video4 y si ha terminado de reproducirse
            if current_video in (videos[1], videos[2], videos[3]):
                # Cambiar al video en bucle (videos[0])
                current_video = videos[0]
                current_video.set(cv2.CAP_PROP_POS_FRAMES, 0)

            continue

        frame = cv2.resize(frame, (screen.get_width(), screen.get_height()))
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        pygame_frame = pygame.image.frombuffer(frame.tobytes(), frame.shape[1::-1], "RGB")

        screen.blit(pygame_frame, (0, 0))
        pygame.display.flip()

        # Salir si se presiona la tecla 'q'
        keys = pygame.key.get_pressed()
        if keys[pygame.K_q]:
            running = False

    # Liberar recursos y cerrar ventanas
    for video in videos:
        video.release()
    cv2.destroyAllWindows()
    pygame.quit()
    ser.close()

if __name__ == "__main__":
    main()
