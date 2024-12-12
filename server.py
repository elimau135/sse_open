import wolfssl
import socket

# Define server IP and port
server_ip = "0.0.0.0"  # Listen on all available interfaces
port = 5000

# Create a TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((server_ip, port))
server_socket.listen(5)

print(f"Server listening on {server_ip}:{port}...")

# Wait for a client to connect
client_socket, client_address = server_socket.accept()
print(f"Connection from {client_address}")

# Create SSL context and wrap the connection with SSL (TLSv1.2 in this case)
context = wolfssl.SSLContext(wolfssl.PROTOCOL_TLSv1_2)
ssl_socket = context.wrap_socket(client_socket, server_side=True)

# Receive data from the client
data = ssl_socket.recv(1024)
print(f"Received from client: {data.decode()}")

# Send a response to the client
response = "Hello from server!"
ssl_socket.send(response.encode())

# Close the connection
ssl_socket.close()
server_socket.close()
