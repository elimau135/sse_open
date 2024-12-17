#source: https://www.dropbox.com/scl/fi/ro661g8c3a1g8r9aphiax/client.py?rlkey=ti9hkq56ja3qw1p78erfq83k5&e=1&dl=0
#from: Culbertson, Cory (2022) Client-Server Communication with Two Raspberry Pies and Python, https://www.youtube.com/watch?v=T3XOac7QmAI 

import socket


host = '192.168.178.54'
port = 5111


s = socket.socket()
s.connect((host,port))
print("Connected to",host)


while True:
    message = input("->")
    s.send(message.encode())  #convert to bytes then send

