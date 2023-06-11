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
        img = np.zeros((300,300,3),np.uint8)
        img[:,:,0] = int(B)
        img[:,:,1] = int(G)
        img[:,:,2] = int(R)
        cv.putText(img, 'R:'+str(int(R)), (10, 30), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        cv.putText(img, 'G:'+str(int(G)), (10, 60), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        cv.putText(img, 'B:'+str(int(B)), (10, 90), cv.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
        cv.imshow('img',img)

        # img_origin = np.zeros((300,300,3),np.uint8)
        # img_origin[:,:,0] = int(RGB[2])
        # img_origin[:,:,1] = int(RGB[1])
        # img_origin[:,:,2] = int(RGB[0])
        # cv.putText(img_origin, "origin", (10, 30), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        # cv.putText(img_origin, 'R:'+str(int(int(RGB[0])*0.003891)), (10, 60), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        # cv.putText(img_origin, 'G:'+str(int(int(RGB[1])*0.003891)), (10, 90), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        # cv.putText(img_origin, 'B:'+str(int(int(RGB[2])*0.003891)), (10, 120), cv.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
        # cv.imshow('img_origin',img_origin)

        key = cv.waitKey(20) & 0xFF
        if key == ord('q'):
            break

ser.close()
