import socket
import asyncio


class lan_server:

    def __init__(self, ip):
        self.ip = ip
        self.main_loop = asyncio.get_event_loop()  # получение event loop
        self.received_data = []  # список для хранения всех принятых запросов и их дальнейшей обработки в программе

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # создание сокета сервера
        self.server.bind(ip)  # назначение сокета на конкретный IP, Port
        self.server.listen(8)  # обозначение сокета как сервера с 8-мью одновременными подключениями
        self.server.setblocking(False)  # set timeout на 0, необходимо для асинхронности

    async def accept_connection(self):  # корутина для принятия подключений
        while True:
            client_socket, address = await self.main_loop.sock_accept(self.server)  # ожидание подключения
            address_str = f'{address[0]}:{address[1]}'
            print(f'{address_str} has connected!')
            # для каждого клиента в event loop создаётся задача чтения его запросов
            self.main_loop.create_task(self.receive_data(client_socket))

    async def receive_data(self, sock):  # корутина чтения запросов
        while True:
            request = None
            try:
                request = await self.main_loop.sock_recv(sock, 2048)  # чтение запроса клиента
                print(f'GOT: {repr(request.decode())}')
                if not request:
                    print('Client disconnected')
                    break
            except ConnectionResetError:  # если клиент отключился, покидается цикл и задача уничтожается
                print('Client disconnected')
                break
            self.received_data.append(request.decode())

    async def _start(self):  # корутина (асинхронная функция) для запуска сервера
        run_server_task = self.main_loop.create_task(self.accept_connection())
        await run_server_task

    def start(self):
        self.main_loop.run_until_complete(self._start())
