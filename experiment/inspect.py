#!/usr/bin/env python
# -*- coding:utf-8 -*-
from __future__ import print_function
import cv2
import os

DATA_DIR = "/Users/DboyLiao/Works/Projects/Avatar-Program/mobile/dev/FaceAlignment/FaceAlignment/COFW_Dataset"

def get_bound(index):
    index = int(index)
    boundbox_path = os.path.join(DATA_DIR, "boundingbox_test.txt")
    with open(boundbox_path, "r") as rf:
        lines = rf.readlines()

    return list(map(lambda s: map(int, s.rstrip().split()), lines))[index]

def main():

    while True:
        image_num = raw_input("Please enter the number of the images: ")
        image_path = os.path.join(DATA_DIR, "testImages", image_num + ".jpg")
        image = cv2.imread(image_path)
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        if image is not None:
            x, y, w, h = get_bound(int(image_num) - 1)
            cv2.rectangle(image, (x, y), (x+w, y+h), (255, 255, 255), 3)
            cv2.imshow(image_num + ".jpg", image)
            cv2.waitKey(0)
            cv2.destroyWindow(image_num + ".jpg")


if __name__ == "__main__":
    main()
