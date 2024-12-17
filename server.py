
#source: https://www.dropbox.com/scl/fi/ro661g8c3a1g8r9aphiax/client.py?rlkey=ti9hkq56ja3qw1p78erfq83k5&e=1&dl=0
#from: Culbertson, Cory (2022) Client-Server Communication with Two Raspberry Pies and Python, https://www.youtube.com/watch?v=T3XOac7QmAI 


import socket


host = ""
port = 5111


s = socket.socket()
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) #avoid reuse error msg
s.bind((host,port))


print ("Server started. Waiting for connection...")
s.listen()
c, addr = s.accept()
print ("Connection from: ",addr)


while True:
    #data is in bytes format, use decode() to transform it into a string
    data = c.recv(1024)
    if not data:
        break
    value = data.decode()
    print ("Received: ",value)
print ("Disconnected. Exiting.")

