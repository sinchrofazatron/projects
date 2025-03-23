import pygame
import tkinter
import numpy as np
from tkinter import *
from PIL import Image, ImageDraw, ImageOps
import math

y_update = 0

img_mat = np.zeros((1000, 1000, 3), dtype = np.uint8)

def bresenham(img, x1, y1, x2, y2, color):
    xchange = False
    if (abs(x1 - x2) < abs(y1 - y2)):
        x1, y1 = y1, x1
        x2, y2 = y2, x2
        xchange = True
    
    if (x1 > x2):
        x1, x2 = x2, x1
        y1, y2 = y2, y1 

    y = y1
    dy = 2.0 * abs((y2 - y1))
    derror = 0.0
    y_update = 1 if y2 > y1 else -1

    for x in range (x1, x2):
        if (xchange):
            img[x, y] = color
        else:
            img[y, x] = color

            derror += dy
            if (derror > (x2 - x1)):
                derror -= 2.0 * (x2 - x1)
                y += y_update

file = open("model_1.obj", "r")
raw = file.readlines()
verts = []
faces = []

for line in raw:
    if line.split(' ')[0].lower() == 'v':
        coords = line.split(' ')[1:4]
        verts.append((float(coords[0]), float(coords[1]), float(coords[2])))
    if line.split(' ')[0].lower() == 'f':
        face = line.split(' ')[1:4]
        faces.append((int(face[0].split('/')[0]), int(face[1].split('/')[0]), int(face[2].split('/')[0])))

for f in range (len(faces)):
    x1 = int(verts[faces[f][0]-1][0]*5000 + 500)
    y1 = int(verts[faces[f][0]-1][1]*5000 + 500)
    x2 = int(verts[faces[f][1]-1][0]*5000 + 500)
    y2 = int(verts[faces[f][1]-1][1]*5000 + 500)
    x3 = int(verts[faces[f][2]-1][0]*5000 + 500)
    y3 = int(verts[faces[f][2]-1][1]*5000 + 500)

    bresenham(img_mat, x1, y1, x2, y2, 255)
    bresenham(img_mat, x1, y1, x3, y3, 255)
    bresenham(img_mat, x2, y2, x3, y3, 255)

img = Image.fromarray(img_mat, mode = 'RGB')
img = ImageOps.flip(img)
img.save('img.png')