import socket
import time


class lan_client:

    def __init__(self, ip):
        self.ip = ip
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # создание объекта сокета
        self._connect()  # запуск корутины _connect

    def _connect(self):  # корутина подключения к переданному ip
        while True:
            try:
                self.client.connect(self.ip)  # попытка подключения к переданному ip
                break
            except ConnectionRefusedError:  # если сервер недоступен
                print('Error, reconnecting...')
                time.sleep(1)

    def send_data(self, data):  # корутина отправки данных
        try:
            self.client.sendall(data.encode())  # отправка данных
            print(f'SENT: {repr(data)}')
        except BrokenPipeError:  # если подключение было разорвано (сервер выключен)
            self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # создание объекта сокета
            self._connect()  # создание нового сокета для переподключения (тут он зависнет пока не подключится)
            self.client.sendall(data.encode())  # отправка данных
            print(f'SENT: {repr(data)}')
