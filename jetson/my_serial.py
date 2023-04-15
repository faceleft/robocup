
import serial
import time


class my_serial1:
    def __init__(self, devise='/dev/ttyUSB0', speed=115200, timeout=1):
        pass
    def connect(self, devise='/dev/ttyUSB0', speed=115200, timeout=1, test = False):
        try:
            self.ser = serial.Serial(devise, speed, timeout=timeout)  # создаём объект класса Serial, с таймаутом
        except:
            return False
        self.ser.flush()  # вообще хз зачем оно надо, но все пишут так что будет
        if test:
            if self.heartbeat() == False:  # вызываем функцию сердцебиения (проверяем связь с Arduino)
               return False
            return True

    def heartbeat(self, Wtime=1):  # функция сердцебиения
        start_time = time.time()
        while True:
            self.write('heartbeat\n')  # отправляет heartbeat
            if self.read() == 'heartbeat':
                return True
                break
            if time.time() - start_time >= Wtime:
                return False
                break
                


    def read(self):  # функция чтения буфера
        line = self.ser.readline().decode().rstrip()
        return str(line)  # возвращает декодированную строку без символов конца строки (\r\n)

    def write(self, data):  # функция отправки данных
        data = str(data)  # создаём строку
        self.ser.write(data.encode("utf-8"))  # отправляем её в закодированном виде
    def bytewrite(self, byte: int):
        self.ser.write(byte)

    def available(self):  # переименованная функция in_waiting
        return self.ser.in_waiting
