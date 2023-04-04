import sys  # импорт sys для добавления модулей в PATH (для импорта кастомных модулей)
sys.path.append('/home/user/Desktop/project/modules/')

from my_serial import my_serial
import time
1
arduino = my_serial()
print("Наличие Ардуино ", end='')
arduino.connect()
time.sleep(10)
print(arduino.heartbeat())
arduino.write("mirror\n")
while True:
    a = int(input())
    if a == -1:
        arduino.write("mirror\n")

    else:
        arduino.bytewrite(chr(a).encode())
        print(ord(chr(a)))
