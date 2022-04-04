
import socket

HOST = "192.168.1.6"  # The server's hostname or IP address
PORT = 23000  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b"*Netlist Solution\nV1 0 node2 5\nR1 node2 node3 5\nR2 node3 0 10\n.end\n*node3")

print("Sent!")
