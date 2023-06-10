import serial
import cv2 as cv    
import numpy as np

R=0;G=0;B=0;C = 65535;
ser = serial.Serial('COM4', 115200)
if ser.isOpen():
    print(ser.name + ' is open...')
    while True:
        data = ser.readline().decode()
        RGB= data.split(',')
        #显示成图像
        try:
            C = int(RGB[3]);R = int(RGB[0])/C*255; G = int(RGB[1])/C*255;B = int(RGB[2])/C*255;
        except:
            continue
        img = np.zeros((500,500,3),np.uint8)
        img[:,:,0] = int(B)
        img[:,:,1] = int(G)
        img[:,:,2] = int(R)
        cv.putText(img, 'R:'+str(R), (10, 30), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        cv.putText(img, 'G:'+str(G), (10, 60), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        cv.putText(img, 'B:'+str(B), (10, 90), cv.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
        cv.imshow('img',img)
        key = cv.waitKey(20) & 0xFF
        if key == ord('q'):
            break

ser.close()
