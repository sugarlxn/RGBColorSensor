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
        self.image = np.zeros((300, 300, 3), np.uint8)
        self.hsv = np.zeros((300, 300, 3), np.uint8)
        self.hls = np.zeros((300, 300, 3), np.uint8)
        self.lab = np.zeros((300, 300, 3), np.uint8)
        self.luv = np.zeros((300, 300, 3), np.uint8)

    def show_image(self):
        self.image[:, :, 0] = self.color.B
        self.image[:, :, 1] = self.color.G
        self.image[:, :, 2] = self.color.R
        cv.putText(self.image, 'B:'+str(self.color.B), (10, 30),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 1)
        cv.putText(self.image, 'G:'+str(self.color.G), (10, 60),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 1)
        cv.putText(self.image, 'R:'+str(self.color.R), (10, 90),
                   cv.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
        cv.imshow('imgbgr', self.image)
        self.hsv = cv.cvtColor(self.image, cv.COLOR_BGR2HSV)
        self.hls = cv.cvtColor(self.image, cv.COLOR_BGR2HLS)
        self.lab = cv.cvtColor(self.image, cv.COLOR_BGR2LAB)
        self.luv = cv.cvtColor(self.image, cv.COLOR_BGR2LUV)

        key = cv.waitKey(25) & 0xFF
        if key == ord('q'):
            self.color.close()
            cv.destroyAllWindows()
            return False


if __name__ == "__main__":
    color = ColoriMeter()
    while True:
        color.color.get_color()
        result = color.show_image()
        if result == False:
            break
    print("break!!!!!")
    sys.exit(0)
