#pip install pyserial
import serial


# Configura el puerto serial
puerto_serial = serial.Serial('COM7', 9600)  # Reemplaza 'COM3' con tu puerto serial

try:
    while True:
        # Lee una línea desde el puerto serial
        sharp = puerto_serial.readline().decode().strip()
        print("Recibido:", sharp)
        if sharp == "SHARP1: 1":
            print("SHARP1 PYTHON")

        
        # Hacer algo con los datos recibidos, como procesarlos o guardarlos en una base de datos, etc.
        
except KeyboardInterrupt:
    # Cierra el puerto serial cuando se interrumpe el programa
    puerto_serial.close()