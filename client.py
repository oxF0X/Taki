import socket
import json
from dataclasses import dataclass

SERVER_IP = "127.0.0.1"
SERVER_PORT = 4444

@dataclass
class Login:
    "useranme" : str
    "password" : str

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)

l = Login("Test", "TheStrongetsPasswordEver")
jsonData = json.load(l)
sock.sendall(bin(10) + bin(len(jsonData).zfill(32) + bin(jsonData)).encode())

server_msg = sock.recv(1024)
print(server_msg.decode())