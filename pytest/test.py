import socket
import cv2
import base64
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

addServer = ('127.0.0.1', 55555)
sock.connect(addServer)

sock.send(b'!123')

capture = cv2.VideoCapture(0)

while True:
    flag, frame = capture.read()
    img_resize = cv2.resize(frame,(640,480))
    (status,img_encode) = cv2.imencode('.jpeg', img_resize)
    data = img_encode.tostring()

    print('data send ...')
    sock.send(b'%123|'+ base64.b64encode(data) +b'&')
    # time.sleep(1)
    frame = capture.read()
