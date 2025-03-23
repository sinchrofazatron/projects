import pygame
import tkinter
import numpy as np
from tkinter import *
from PIL import Image, ImageDraw, ImageOps
import math
import random

y_update = 0

img_mat = np.zeros((1000, 1000, 3), dtype = np.uint8)

z_buf = np.full((1000, 1000), np.inf, dtype = np.float32)

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

def print_rectangle(img, buffer):

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
        z1 = int(verts[faces[f][0]-1][2]*5000 + 500)
        x2 = int(verts[faces[f][1]-1][0]*5000 + 500)
        y2 = int(verts[faces[f][1]-1][1]*5000 + 500)
        z2 = int(verts[faces[f][1]-1][2]*5000 + 500)
        x3 = int(verts[faces[f][2]-1][0]*5000 + 500)
        y3 = int(verts[faces[f][2]-1][1]*5000 + 500)
        z3 = int(verts[faces[f][2]-1][2]*5000 + 500)

        # color = random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)

        # bresenham(img_mat, x1, y1, x2, y2, 255)
        # bresenham(img_mat, x1, y1, x3, y3, 255)
        # bresenham(img_mat, x2, y2, x3, y3, 255)

        x = x2 - x3
        y = y2 - y3
        z = z2 - z3

        v1 = [x, y, z]

        x_ = x2 - x1
        y_ = y2 - y1
        z_ = z2 - z1

        v2 = [x_, y_, z_]

        n = np.cross(v1, v2)

        watcher = [0, 0, 1]

        cos_alpha = np.dot(n, watcher)/(np.linalg.norm(n) * np.linalg.norm(watcher))
        angle_rad = np.arccos(np.clip(cos_alpha, -1.0, 1.0))
        angle_deg = np.degrees(angle_rad)

        color = (0, -255*cos_alpha, 0)

        if(angle_deg < math.degrees(math.pi/2)):
            f += 1
        else:
            xmin = min(x1, x2, x3)
            if (xmin < 0):
                xmin = 0
        
            xmax = max(x1, x2, x3)

            ymin = min(y1, y2, y3)
            if (ymin < 0):
                ymin = 0

            ymax = max(y1, y2, y3)
            if (ymin < 0):
                ymin = 0

            for y in range(ymin, ymax):
                for x in range(xmin, xmax):
                    if ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3) != 0):

                        lambda0 = ((x - x3) * (y2 - y3) - (x2 - x3) * (y - y3)) / ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) 
                        lambda1 = ((x1 - x3) * (y - y3) - (x - x3) * (y1 - y3)) / ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3))
                        lambda2 = 1.0 - lambda0 - lambda1

                        if (lambda0 >= 0 and lambda1 >= 0 and lambda2 >= 0):
                            zck = lambda0*z1 + lambda1*z2 + lambda2*z3
                            if (zck > buffer[x, y]):
                                x += 1
                            if (zck < buffer[x, y]):
                                img[x, y] = color
                                buffer[x, y] = zck            
            y += 1

        
        
print_rectangle(img_mat, z_buf)
buffer = Image.fromarray(z_buf, mode = 'RGB')
img = Image.fromarray(img_mat, mode = 'RGB')
img = ImageOps.flip(img)
img.save('img6.png')
img.show()