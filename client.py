import socket
import json
from dataclasses import dataclass
import struct
import base64

SERVER_IP = "127.0.0.1"
SERVER_PORT = 4444

l = {"username": "test", "password": "123"}
#l = {"username": "test", "password": "123", "email": "dfsf@gmail.com", "address" : "dd,1,dd", "phoneNumber" : "053-2223-333", "birthday" : "11/02/2023"}
jsonData = json.dumps(l)

binary_string = format(len(jsonData))

code = struct.pack('>B', 10)

size = struct.pack('I', len(jsonData))


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)

sock.sendall(code + size + jsonData.encode())
print(jsonData)
print(sock.recv(1024).decode())
