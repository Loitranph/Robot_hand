"""
--------------------------------------------------------------------------
-*- coding: utf-8 -*-                created on sunday, november, 26, 2023

@author: Phuoc Loi Tran
@student code: 2101076 (from C.T.U.T)
@github: Loitranph (https://github.com/Loitranph)
@discr|pt|on: Gesture recognition and control project, using python and arduino
@using:
  software:
            python:
                    version: 3.10.7
                    lib: openCV, mediapipe, pyserial, time, numpy...
            arduino:
                    ide version: 2.2.1
                    lib: Arduino.h, Servo.h
  hardware:
            board Arduino uno
            ...

-----------------------------------------------------------------------------

"""

import mediapipe as mp
import numpy as np
import cv2 as cv
import serial
import time

# Setup
mp_drawing_util = mp.solutions.drawing_utils
mp_drawing_style = mp.solutions.drawing_styles
mp_hand = mp.solutions.hands
hands = mp_hand.Hands(model_complexity=0, min_detection_confidence=0.5, min_tracking_confidence=0.5)

cap = cv.VideoCapture(0)

DataSerial = serial.Serial('COM3', 9600)
time.sleep(10)

# Main loop
while cap.isOpened():
    success, img = cap.read()
    if not success:
        print("Error: Failed to open camera")
        break

    # Process img
    img = cv.cvtColor(img, cv.COLOR_BGR2RGB)
    result = hands.process(img)
    img = cv.cvtColor(img, cv.COLOR_RGB2BGR)

    if result.multi_hand_landmarks:
        myHand = []

        for idx, hand in enumerate(result.multi_hand_landmarks):
            mp_drawing_util.draw_landmarks(img, hand, mp_hand.HAND_CONNECTIONS,
                                           mp_drawing_style.get_default_hand_landmarks_style(),
                                           mp_drawing_style.get_default_hand_connections_style())

            lbl = result.multi_handedness[idx].classification[0].label
            if lbl == "Right":
                landmarks = np.array([[lm.x, lm.y] for lm in hand.landmark])
                landmarks_pixels = np.multiply(landmarks, [img.shape[1], img.shape[0]])

                standard_distance = np.linalg.norm(landmarks_pixels[0] - landmarks_pixels[17])
                distances_array = [np.linalg.norm(landmarks_pixels[4] - landmarks_pixels[17]),
                                   np.linalg.norm(landmarks_pixels[0] - landmarks_pixels[8]),
                                   np.linalg.norm(landmarks_pixels[0] - landmarks_pixels[12]),
                                   np.linalg.norm(landmarks_pixels[0] - landmarks_pixels[16]),
                                   np.linalg.norm(landmarks_pixels[0] - landmarks_pixels[20]),
                                   np.linalg.norm(landmarks_pixels[5] - landmarks_pixels[17])]
                distance_encoding = str([0] + [int(dist * 100 / standard_distance) for dist in distances_array])+'/n'
                DataSerial.write(distance_encoding.encode())
                print(distance_encoding)
        time.sleep(1/9)

    cv.imshow("Created by Phuoc Loi Tran 2101076", img)
    key = cv.waitKey(1)
    if key == 27:
        break
cap.release()
cv.destroyAllWindows()
