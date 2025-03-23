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

def parser(img, buffer):
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

    rotate(verts)

    render(verts, faces, img, buffer)
    

def rotate(verts):
    a = 45
    b = 45
    c = 45
    matrixR1 = [[1, 0, 0], [0, np.cos(a), np.sin(a)], [0, (-1) * np.sin(a), np.cos(a)]]
    matrixR1 = np.array(matrixR1)
    matrixR2 = [[np.cos(b), 0, np.sin(b)], [0, 1, 0], [(-1)*np.sin(b), 0, np.cos(b)]]
    matrixR2 = np.array(matrixR2)
    matrixR3 = [[np.cos(c), np.sin(c), 0], [(-1) * np.sin(c), np.cos(c), 0], [0, 0, 1]]
    matrixR3 = np.array(matrixR3)
    R = np.dot(matrixR1, matrixR2, matrixR3)
    # R = matrixR2

    # for v in range (len(verts)):
    #     verts[v] = R@verts[v]
    # print(verts[0])
    # return verts

    txyz = (0.002, 0.0001, 0.2)

    t = np.array(txyz)
    print(t)

    for v in range (len(verts)):
        verts[v] = R@verts[v] + t
    print(verts[0])
    return verts

def render(verts, faces, img, buffer):
     for f in range (len(faces)):
        x1 = (verts[faces[f][0]-1][0])
        y1 = (verts[faces[f][0]-1][1])
        z1 = (verts[faces[f][0]-1][2])
        px1 = (1000*x1)/z1 + 500
        py1 = (1000*y1)/z1 + 500
        x2 = (verts[faces[f][1]-1][0])
        y2 = (verts[faces[f][1]-1][1])
        z2 = (verts[faces[f][1]-1][2])
        px2 = (1000*x2)/z2 + 500
        py2 = (1000*y2)/z2 + 500
        x3 = (verts[faces[f][2]-1][0])
        y3 = (verts[faces[f][2]-1][1])
        z3 = (verts[faces[f][2]-1][2])
        px3 = (1000*x3)/z3 + 500
        py3 = (1000*y3)/z3 + 500

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
            xmin = int(min(px1, px2, px3))
            if (xmin < 0):
                xmin = 0
        
            xmax = int(max(px1, px2, px3))+1

            ymin = int(min(py1, py2, py3))
            if (ymin < 0):
                ymin = 0

            ymax = int(max(py1, py2, py3))+1
            if (ymin < 0):
                ymin = 0

            for y in range(ymin, ymax):
                for x in range(xmin, xmax):
                    if ((px1 - px3) * (py2 - py3) - (px2 - px3) * (py1 - py3) != 0):

                        lambda0 = ((x - px3) * (py2 - py3) - (px2 - px3) * (y - py3)) / ((px1 - px3) * (py2 - py3) - (px2 - px3) * (py1 - py3)) 
                        lambda1 = ((px1 - px3) * (y - py3) - (x - px3) * (py1 - py3)) / ((px1 - px3) * (py2 - py3) - (px2 - px3) * (py1 - py3))
                        lambda2 = 1.0 - lambda0 - lambda1

                        if (lambda0 >= 0 and lambda1 >= 0 and lambda2 >= 0):
                            zck = lambda0*z1 + lambda1*z2 + lambda2*z3
                            if (zck > buffer[x, y]):
                                x += 1
                            if (zck < buffer[x, y]):
                                img[x, y] = color
                                buffer[x, y] = zck            
            y += 1
  
parser(img_mat, z_buf)
buffer = Image.fromarray(z_buf, mode = 'RGB')
img = Image.fromarray(img_mat, mode = 'RGB')
img = ImageOps.flip(img)
img.save('img12.png')
img.show()