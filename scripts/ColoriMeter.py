import serial
import cv2 as cv
import numpy as np
import threading
import sys
import matplotlib.pyplot as plt



class raw_data_keeper():
    def __init__(self):
        self.R = 0
        self.G = 0
        self.B = 0
        self.C = 65535
        self.ser = serial.Serial('COM4', 115200)
        if self.ser.isOpen():
            print(self.ser.name + ' is open...')
        else:
            print(self.ser.name + ' is not open...')
            sys.exit(1)

    def get_color(self):
        data = self.ser.readline().decode()
        RGB = data.split(',')
        # 显示成图像
        try:
            C1 = int(RGB[3])
            R1 = int(RGB[0])/C1*255
            G1 = int(RGB[1])/C1*255
            B1 = int(RGB[2])/C1*255
            self.R = int(R1)
            self.G = int(G1)
            self.B = int(B1)
        except:
            pass
        return self.R, self.G, self.B

    def close(self):
        self.ser.close()


class ColoriMeter():
    def __init__(self) -> None:
        self.color = raw_data_keeper()
        self.image = np.zeros((500, 500, 3), np.uint8)
        self.hsv = np.zeros((3, 3, 3), np.uint8)
        self.hls = np.zeros((3, 3, 3), np.uint8)
        self.lab = np.zeros((3, 3, 3), np.uint8)
        self.luv = np.zeros((3, 3, 3), np.uint8)
        self.xyz = np.zeros((3, 3, 3), np.uint8)
        self.sample_lab_list = []

    def show_image(self):
        self.image[:, :, 0] = self.color.B
        self.image[:, :, 1] = self.color.G
        self.image[:, :, 2] = self.color.R
        cv.putText(self.image, 'B:'+str(self.color.B), (10, 30),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (0,0,255), 1)
        cv.putText(self.image, 'G:'+str(self.color.G), (10, 60),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 1)
        cv.putText(self.image, 'R:'+str(self.color.R), (10, 90),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (255,0,0), 1)
        self.hsv = cv.cvtColor(self.image, cv.COLOR_BGR2HSV)
        self.hls = cv.cvtColor(self.image, cv.COLOR_BGR2HLS)
        self.lab = cv.cvtColor(self.image, cv.COLOR_BGR2LAB)
        # self.luv = cv.cvtColor(self.image, cv.COLOR_BGR2LUV)
        # self.xyz = cv.cvtColor(self.image, cv.COLOR_BGR2XYZ)
        cv.putText(self.image, 'L:'+str(self.lab[0, 0, 0]), (10, 120),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (0,0,0), 1)  
        cv.putText(self.image, 'a:'+str(self.lab[0, 0, 1]), (10, 150),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (0,0,0), 1)
        cv.putText(self.image, 'b:'+str(self.lab[0, 0, 2]), (10, 180),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (0,0,0), 1)
       
        cv.imshow('imgbgr', self.image)

        key = cv.waitKey(10) & 0xFF
        if key == ord('q'):
            self.color.close()
            cv.destroyAllWindows()
            return False
        # elif key == ord('s'):
        #     self.sample_lab_list.append((self.lab[0, 0, :], [self.color.B, self.color.G, self.color.R]))
        #     print("save one sample")
        # elif key ==ord('p'):
        #     if(len(self.sample_lab_list) >= 2):
        #         print(self.sample_lab_list)
        #         lab1 = self.sample_lab_list.pop()
        #         lab2 = self.sample_lab_list.pop()
        #         deltaL = lab1[0][0] - lab2[0][0]
        #         deltaA = lab1[0][1] - lab2[0][1]
        #         deltaB = lab1[0][2] - lab2[0][2]
        #         deltaE = np.sqrt(deltaL**2 + deltaA**2 + deltaB**2)
        #         print("deltaE=",deltaE)
        #         delta_image = np.zeros((300, 300, 3), np.uint8)
        #         delta_image[:150, :150, 0] = lab1[1][0]
        #         delta_image[:150, :150, 1] = lab1[1][1]
        #         delta_image[:150, :150, 2] = lab1[1][2]
        #         delta_image[150:300, 150:300, 0] = lab2[1][0]
        #         delta_image[150:300, 150:300, 1] = lab2[1][1]
        #         delta_image[150:300, 150:300, 2] = lab2[1][2]
        #         cv.imshow('delta', delta_image)
        #         cv.waitKey(0)
        #         cv.destroyWindow('delta')
        #         self.sample_lab_list.clear()
        #     else:
        #         print("sample_lab_list is not enough!")

if __name__ == "__main__":
    color = ColoriMeter()
    while True:
        color.color.get_color()
        result = color.show_image()
        if result == False:
            break
    print("break!!!!!")
    sys.exit(0)
