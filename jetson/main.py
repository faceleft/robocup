import sys  # импорт sys для добавления модулей в PATH (для импорта кастомных модулей)
sys.path.append('/home/user/Desktop/project/modules/')
#sys.path.append('Z:\\Users\\face-\\Desktop\\robocup\\modules\\')
from pose_module import pose_module
from my_serial import my_serial1
from Vector import Vector
#import pygame
import time
import cv2
import math
import numpy as np
print("******************************")
print("Библиотеки подключены")
arduino = my_serial1()
print("Наличие Ардуино ", end='')
arduino.connect('/dev/ttyUSB0')
time.sleep(10)
print(arduino.heartbeat())

class Controller:
    controller = None
    axis_data = None
    button_data = None
    hat_data = None
    def __init__(self, num):
        pygame.init()
        pygame.joystick.init()
        self.controller = pygame.joystick.Joystick(num)
        self.controller.init()
    def listen(self, num):
        """Listen for events to happen"""
        if not self.axis_data:
            self.axis_data = {}

        if not self.button_data:
            self.button_data = {}
            for i in range(self.controller.get_numbuttons()):
                self.button_data[i] = False

        if not self.hat_data:
            self.hat_data = {}
            for i in range(self.controller.get_numhats()):
                self.hat_data[i] = (0, 0)
        for event in pygame.event.get():
            if event.type == pygame.JOYAXISMOTION:
                self.axis_data[event.axis] = round(event.value,2)
            elif event.type == pygame.JOYBUTTONDOWN:
                self.button_data[event.button] = True
            elif event.type == pygame.JOYBUTTONUP:
                self.button_data[event.button] = False
            elif event.type == pygame.JOYHATMOTION:
                self.hat_data[event.hat] = event.value
        out = (self.axis_data, self.button_data, self.hat_data)
        return out[num]

class Vector(list):
    def __add__(self, other):
        return Vector(map(lambda x, y: x + y, self, other))

    def __sub__(self, other):
        return Vector(map(lambda x, y: x - y, self, other))

    def __neg__(self):
        return Vector(map(lambda x: -x, self))

    def __truediv__(self, other):
        return Vector(map(lambda x: x / other, self))

    def __mul__(self, other):
        return Vector(map(lambda x: x * other, self))

    def length(self):
        return sum(map(lambda x: x ** 2, self)) ** 0.5

    @staticmethod
    def emptyVector(directions_len):
        return Vector([0 for _ in range(directions_len)])

    @staticmethod
    def toVector(scalar, direction):
        return Vector([i * scalar / Vector(direction).length() for i in direction]) if scalar != 0 else Vector().emptyVector(len(direction))

def world_landmarks(marks, res):
    dots = [Vector([i.x, i.y * (res[1] / res[0]), i.z / 2]) for i in marks]
    visibility = [i.visibility for i in marks]
    centre = (dots[11] + dots[12] + dots[23] + dots[24]) / 4
    k = (dots[11] - dots[12]).length()
    k = 0.26/(k-0.04)
    for c, dot in enumerate(dots):
        dots[c] = (centre - dot) * k
    return dots, visibility, k, centre[0]

def view(wlms, vis):
    res = (800, 600, 1)
    blank = np.zeros(res, dtype='uint8')
    centre = Vector([300, -250, 0])
    k = 100/(wlms[11]-wlms[12]).length()
    #for wlm in wlms:
    #    pos = (wlm*k)+centre
    #    cv2.circle(blank, (int(pos[0]), int(pos[1])), int(3+wlm[2]*2), 64, cv2.FILLED)


    for c, wlm in enumerate(wlms):
        wlm_pos = (int(-(k*wlm[0] - 300)), int(-(k*wlm[1] - 250)))
        #print("!!!",wlm_pos,"!!!")
        if vis[c] <= global_visibility:
            cv2.circle(blank, wlm_pos, 4, 64, cv2.FILLED)
        else:
            cv2.circle(blank, wlm_pos, 5, 256, cv2.FILLED)

        #cv2.putText(blank, str(c),(wlm_pos[0]+100, wlm_pos[1]+100), cv2.FONT_HERSHEY_SIMPLEX, 200, 5)

    #print(str(wlms[15]))
    cv2.circle(blank, (50,50), 8, 200, cv2.FILLED)
    cv2.imshow('Pose', blank)
    cv2.waitKey(1)

def detect(wlms):
    global arduino
    #left = [23, 11, 13]
    #right = [24, 12, 14]
    rects = ((12, 11, 13), (11, 12, 14))
    #rects = ((23, 11, 13)) #13/23
    for dots in rects:
        A = [wlms[dots[1]][0], wlms[dots[1]][1]]
        B = [wlms[dots[0]][0], wlms[dots[0]][1]]
        C = [wlms[dots[2]][0], wlms[dots[2]][1]]
        a = Vector(Vector(C)-Vector(B)).length()
        b = Vector(Vector(A)-Vector(C)).length()
        c = Vector(Vector(A)-Vector(B)).length()

        cos = ((b**2)+(c**2)-(a**2))/(2*b*c)

        angle = ((math.degrees(math.acos(cos))-90)/90)*255
        tan = (1-(b/c))*255

        #print(dots[1], angle, tan)
        if dots[1] == 11:
            byt = bytes([min(max(0,int(angle)), 255)])
            #print(byt)
            #arduino.write(byt)

def detect_angle(dots):
    a = (dots[0]-dots[2]).length()
    b = (dots[0]-dots[1]).length()
    c = (dots[2]-dots[1]).length()
    cos = ((b**2)+(c**2)-(a**2))/(2*b*c)
    angle = math.degrees(math.acos(cos))
    return angle

def serial_monitor():
    if arduino.available():
        return arduino.read()
    else: 
        return None
def toByte(val, min_, max_):
    return (round(min(max(val-min_, 0), max_-min_)*(253.0/(max_-min_)))+2).to_bytes(1, "big")


def main():
    global cap
    global switch
    global other_ready
    global final_sign
    prev_time = time.time()
    while True:
        cur_time = time.time()
        
        inp = serial_monitor()
        if inp == "#complited":
            flag = 0
        if inp == "start":
            switch=1
            arduino.write("mirror\n")
        #print(inp, flag)
        success, img = cap.read()
        if not success:
            continue
        
        img = detector.process(img)
        lms = detector.get_landmarks()
        if lms:
            wlms, visible, k, centre = world_landmarks(lms, (int(cap.get(3)), int(cap.get(4))))
            if switch == 1:
                angle_r = detect_angle([wlms[13],wlms[11],wlms[23]])
                angle_l = detect_angle([wlms[14],wlms[12],wlms[24]])
                min_=20
                max_=180
                #print((round(min(max(angle_r-min_, 0), max_-min_)*(253.0/(max_-min_)))+2))
                print(wlms[16][2]-wlms[12][2], wlms[15][2]-wlms[11][2])
                arduino.bytewrite((1).to_bytes(1, "big"))
                arduino.bytewrite(toByte(wlms[15][2]-wlms[11][2], 0, 1))
                arduino.bytewrite(toByte(wlms[16][2]-wlms[12][2], 0, 1))
                arduino.bytewrite(toByte(angle_r, 20, 180))
                arduino.bytewrite(toByte(angle_l, 20, 180))
                arduino.bytewrite(toByte(centre, 0, 1))
                arduino.bytewrite(toByte(k/5, 0, 1))
                if angle_r>160 and angle_l>160:
                    arduino.bytewrite((0).to_bytes(1, "big"))
                    arduino.write("fight\n")
                    switch=2
                #detect(wlms)

            view(wlms, visible)
        frame_time = round(1/(cur_time - prev_time), 1)
        cv2.putText(img, str(frame_time) + "fps", (40, 50),
                    cv2.FONT_HERSHEY_PLAIN, 1.5, (0, 0, 255), 2)
        cv2.imshow("Image", img)
        cv2.waitKey(1)
        prev_time = cur_time

dispW = 400
dispH = 240
i = 0

while True: 
    cap = cv2.VideoCapture(i)
    font=cv2.FONT_HERSHEY_SIMPLEX
    cap.set(cv2.CAP_PROP_FRAME_WIDTH,dispW)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT,dispH)
    cap.set(5, 30)
    cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)
    width, height = int(cap.get(3)), int(cap.get(4))
    fps = int(cap.get(5))

    if width == 0 or height == 0 or fps == 0:
        print("Попытка подключиться к камере ", i)
        i=i+1
        if i>10:
            print("Камера не найдена")
            exit()
    else:
        print(f'Camera resolution: {width}x{height}, FPS: {fps}')
        break
    
time.sleep(1)
detector = pose_module()
#gamepad = Controller(0)
switch = 0
other_ready = False
final_sign = ''

global_visibility = 0.5


rects_left = [((600-60, 10), (600-140, 90)), ((600-140, 10), (600-220, 90)),
              ((600-60, 90), (600-140, 170)), ((600-140, 90), (600-220, 170)),
              ((600-60, 170), (600-140, 250)), ((600-140, 170), (600-220, 250))]
rects_right = [((60, 10), (140, 90)), ((140, 10), (220, 90)),
              ((60, 90), (140, 170)), ((140, 90), (220, 170)),
              ((60, 170), (140, 250)), ((140, 170), (220, 250))]              


main()
