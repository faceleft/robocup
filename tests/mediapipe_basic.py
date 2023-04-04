import sys  # импорт sys для добавления модулей в PATH (для импорта кастомных модулей)
sys.path.append('/home/user/Desktop/project/modules/')

import cv2 as cv
from pose_module import pose_module

#cap = cv.VideoCapture(0, cv.CAP_DSHOW)
cap = cv.VideoCapture(0)
cap.set(cv.CAP_PROP_BUFFERSIZE, 1)
pm = pose_module()

while True:
    success, image = cap.read()
    
    #print(image, success)
    if success == True:
        img = pm.process(image)
        lms = pm.get_landmarks(image)

        cv.imshow("Image", image)
        cv.waitKey(1)

cv.destroyAllWindows()
