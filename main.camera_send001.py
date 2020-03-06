import socket
import cv2
import base64
import time
import os
import pigpio

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
face_cascade = cv2.CascadeClassifier('/usr/local/lib/python3.7/dist-packages/cv2/data/haarcascade_frontalface_default.xml')

#camera
SERVO_PIN = 21
pi = pigpio.pi()
pi.set_PWM_frequency(SERVO_PIN,50)
line = 0

#TCP
#addServer = ('10.42.0.1', 55555)
addServer = ('192.168.2.175', 55555)
sock.connect(addServer)
sock.send(b'!123')

cap = cv2.VideoCapture(0)


#kurosu_data001_start
cap.set(cv2.CAP_PROP_FPS, 30)
#cap.set(cv2.CAP_PROP_FRAME_WIDTH, 300)
#cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 300)
#print(cap.get(cv2.CAP_PROP_FPS))
#print(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
#print(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

flag, frame = cap.read()
#height, widit, channels = frame.shape
#kurosu_data001_end


while(flag == True):

    msg = sock.recv(10)
    if "PL" == msg:
	    pi.set_servo_pulsewidth(SERVO_PIN, 700)

    elif "PR" == msg:
	    pi.set_servo_pulsewidth(SERVO_PIN, 2100)
    else:
	    pi.set_servo_pulsewidth(SERVO_PIN, 0)

    #kurosu_data002_start
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # gray = frame
    
    img_resize = cv2.resize(gray,(300,300))
    (status,img_encode) = cv2.imencode('.jpeg', img_resize)
    data = img_encode.tostring()
    encode_data = base64.b64encode(data)
    sock.send(b'%123|'+ encode_data +b'&')
    
    faces = face_cascade.detectMultiScale(gray)
    if len(faces) != 0 :
        if line > 10:
            cv2.imwrite('/home/ubuntu/Documents/face.jpg', gray)
            os.system("./line.sh")
            line = 0
        else:
            line = line + 1

    for (x,y,w,h) in faces:
        color = (0, 0, 225)
        pen_w = 3
        cv2.rectangle(gray, (x, y), (x+w, y+h), color, thickness = pen_w)
    
    cv2.imshow("kuro", gray)
    key = cv2.waitKey(1)
    if (key == "q"):
        break
    
    flag, frame = cap.read()
    #kurosu_data002_end
       
cap.release()
cv2.destroyAllWindows()
