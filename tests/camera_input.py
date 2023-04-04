import cv2 as cv

cap = cv.VideoCapture(0)

while True:
    success, image = cap.read()

    cv.imshow("Image", image)
    cv.waitKey(1)