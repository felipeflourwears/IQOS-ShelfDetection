# Librerias Python
´´´
pip install pygame
pip install opencv-python
pip install numpy
pip install pyserial
´´´

## Driver LabSillicon
´´´
https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
´´´

### Path to init application when Windows start
´´´
cd C:\Users\<Nombre de usuario>\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
´´´

### File .bat
You need to manipulate the root to script
´´´
@echo off
cd "C:\Users\HP\Documents\IQOS-ShelfDetection-master"
python change.py
pause
´´´