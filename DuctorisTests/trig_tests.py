import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import math
import sys
from enum import Enum

def convertRadian2Degree(alpha):
   return (alpha * 180 / math.pi)

def convertDegree2Radian(beta):
    return (beta * math.pi) / 180

def getInitAxis(x, y):
    ax = np.linspace(-x * 2, x * 2)
    ay = np.linspace(-y * 2, y * 2)

    px = np.zeros(len(ax))
    py = np.zeros(len(ay))

    plt.axis([(ax[0]), (ax[-1] + 1) ,(ay[0] - 1), (ay[-1] + 1)])
    return ax, px, ay, py

def calcAndDrawPolarCoords(x, y):
    R = math.sqrt(pow(x, 2) + pow(y, 2))
    alpha = math.acos(x / R)    
    xp_1 = np.linspace(0, x, 10)
    yp_1 = np.linspace(0, y, 10)
    xp_2 = np.ones(len(yp_1)) * x
    return R, alpha, xp_1, xp_2, yp_1
    
def rotateAxis(ax, px, ay, py, theta):
    r_ax = []
    r_px = []
    r_ay = []
    r_py = []
    for x in ax:
        r_ax.append(x * math.cos(theta))        
        r_px.append( x * math.sin(theta))        
    for y in ay:
        r_ay.append(y * math.sin((math.pi / 2) + theta))
        r_py.append(y * math.cos((math.pi / 2) + theta))
    return r_ax, r_px, r_ay, r_py

def rotateMirroredAxis(ax, px, ay, py, theta):
    r_ax = []
    r_px = []
    r_ay = []
    r_py = []
    for x in ax:
        r_ax.append(x * math.cos(theta))        
        r_px.append(x * math.sin(theta))        
    for y in ay:
        r_ay.append(y * math.cos(-theta))
        r_py.append(y * math.sin(-theta))
    return r_ax, r_px, r_ay, r_py

def drawAxis(ax, px, ay, py, style):
    plt.plot(ax, px, style)
    plt.plot(py, ay, style)
    plt.plot([ax[-1]], [px[-1]], 'g->')
    plt.text(ax[-1], px[-1] - 1, 'x')
    plt.plot([py[-1]], [ay[-1]], 'g^')
    plt.text(py[-1] - 1, ay[-1], 'y') 

def drawMirroredAxis(ax, px, ay, py, style):
    plt.plot(ax, px, style)
    plt.plot(py, ay, style)
    plt.plot([ax[-1]], [px[-1]], 'g->')
    plt.text(ax[-1], px[-1] - 1, 'x')
    plt.plot([py[0]], [ay[0]], 'g^')
    plt.text(py[0] - 1, ay[0], 'y')
 
 
def transXY2Mirrored(x, y):
    return x, -y

def transformPointToRotatedAxis(x, y, theta):
    R = math.sqrt(pow(x, 2) + pow(y, 2))
    alpha = math.acos(x / R) 
    r_x = R * math.cos(alpha - theta)
    r_y = R * math.sin(alpha - theta)
    return r_x, r_y

def transformPointToRotatedAxis_Mirrored(x, y, theta):
    R = math.sqrt(pow(x, 2) + pow(y, 2))
    r_x = x
    r_y = y
    if x != 0 and y != 0:
        alpha = math.atan2(y, x)
        r_x = R * math.cos(alpha + theta)
        r_y = R * math.sin(alpha + theta)        
    else:
        if x == 0 and  y != 0:
            r_x = abs(y) * math.sin(theta)
            r_y = abs(y) * math.cos(theta)
        if x != 0 and y == 0:
            r_x = abs(x) * math.cos(theta)
            r_y = abs(x) * math.sin(theta)
    return r_x, r_y


#TODO

def checkRegion(x, y, w, h, theta):    
    region_colors = {'Front': 'ko', 'Flank': 'go', 'Rear': 'ro'}
    color = region_colors['Rear']
    regions = {'ko': 'Front', 'go': 'Flank', 'ro': 'Rear'}
    if x > w and y > h:
        #region I
        #transform point to rotated axis 
        r_x, r_y = transformPointToRotatedAxis_Mirrored(x, y, (math.pi / 2) - theta)
        #rotated axis is translated 
        if r_x + (h * math.cos(theta)) - (w * math.sin(theta)) > 0:
            color = region_colors['Flank']
        else:
            color = region_colors['Front']
    elif x > w and y < 0:
        #region II
        r_x, r_y = transformPointToRotatedAxis_Mirrored(x, y, (math.pi / 2) + theta)
        #rotated axis is translated 
        if r_x + w * math.sin(theta) > 0:
            color = region_colors['Rear']
        else:
            color = region_colors['Flank']
    elif x < 0 and y < 0:
        #region III
        r_x, r_y = transformPointToRotatedAxis_Mirrored(x, y, (math.pi / 2) - theta)     
        if r_x > 0:
            color = region_colors['Rear']
        else:
            color = region_colors['Flank']
    elif x < 0 and y > h:
        #region IV
        r_x, r_y = transformPointToRotatedAxis_Mirrored(x, y, (math.pi / 2) + theta)
        #rotated axis is translated 
        if r_x + h * math.cos(theta) > 0:
            color = region_colors['Flank']
        else:
            color = region_colors['Front']
    else:
        #check normal regions
        if x <= w and x >= 0 and y >= h:
            color = region_colors['Front']
        elif x >= w and y >= 0 and y <= h:
            color = region_colors['Flank']
        elif x <= 0 and y <= h and y >= 0:
            color = region_colors['Flank']
        elif x >= 0 and x <= w and y < 0:
            color = region_colors['Rear']
    #TODO - draw the color and point, and name of region in which it is
    plt.text(x + 1, -y - 2, r'XY= {0:.1f}; {1:.1f}'.format(*[ x, y]))
    plt.plot([x], [-y], color)
    
    return

def drawSpriteRectangle(x, y, w, h):
    axis = plt.gca()
    rect = patches.Rectangle((x, y), w, h, edgecolor='r', facecolor='none', linestyle='-.', linewidth=1.5)
    axis.add_patch(rect)
    return

def drawSpriteAreasAndBorders(ax, px, ay, py, w, h, theta):
    #plot the region I axis
    r_ax, r_px, r_ay, r_py = rotateMirroredAxis(ax, px, ay, py, (math.pi / 2) - theta)
    #translate the y axis
    r_py, r_ay = translateAxis_Mirror(r_py, r_ay, 0, y - (w * math.tan(theta)))
    drawMirroredAxis(r_ax, r_px, r_ay, r_py, 'm--')
    #plot the region III axis
    r_ax, r_px, r_ay, r_py = rotateMirroredAxis(ax, px, ay, py, (math.pi / 2) - theta)
    drawMirroredAxis(r_ax, r_px, r_ay, r_py, 'g--')
    #-----------------------------
    #plot the region II 
    r_ax, r_px, r_ay, r_py = rotateMirroredAxis(ax, px, ay, py, (math.pi / 2) + theta)    
    #translate the y axis
    r_py, r_ay = translateAxis_Mirror(r_py, r_ay, 0, math.tan(theta) * w)
    drawMirroredAxis(r_ax, r_px, r_ay, r_py, 'k--')
    #plot the region IV
    r_ax, r_px, r_ay, r_py = rotateMirroredAxis(ax, px, ay, py, (math.pi / 2) + theta)    
    #translate the y axis
    r_py, r_ay = translateAxis_Mirror(r_py, r_ay, 0, h)
    drawMirroredAxis(r_ax, r_px, r_ay, r_py, 'c--')

    return

def translateAxis_Mirror(ax, ay, tx, ty):
    ax_1 = []
    ay_1 = []
    for x in ax:
        ax_1.append( x + tx)
    for y in ay:
        ay_1.append(y  - ty)
    return ax_1, ay_1

if len(sys.argv) > 3:
    x = float(sys.argv[1])
    y = float(sys.argv[2])
    theta = convertDegree2Radian(float(sys.argv[3]))
    if x * y > 0: 
#        plt.figure()
        R, alpha, xp_1, xp_2, yp_1 = calcAndDrawPolarCoords(x, y)

        print "x = " + str(x) + " y= " + str(y) + " alpha = " + str(convertRadian2Degree(alpha))

       # plt.plot([x], [y], 'ko')

        # ax - x points that draw x axis, px - y points that define y position of each x point,
        #in initial not rotated is all zeros
        # ay - y points that draw y axis, py - x points that define x position of each y point,
        #all zeros for not rotated axis
        ax, px, ay, py = getInitAxis(x, y)
        #drawAxis(ax, px, ay, py, 'b')
        #plt.text(x + 0.5, y + 0.5, 'XY: (' + str(x) + '; ' + str(y) + ')')

        #draw rotated axis by passed theta
        #r_ax, r_px, r_ay, r_py = rotateAxis(ax, px, ay, py, theta)
        #drawAxis(r_ax, r_px, r_ay, r_py, 'k--')

        #r_x, r_y = transformPointToRotatedAxis(x, y, theta)
        #plt.text(x + 2, y + 2, 'XY_1: (' + str(r_x) + '; ' + str(r_y) + ')')

        #New figure - mirrored coordinates system - reversed y axis -> canvas in qml
#        fig = plt.figure()
        plt.axis([(ax[0]), (ax[-1] + 1) ,(ay[0]), (ay[-1] + 1)])
        axis = plt.plot([x], [-y], 'ko')

        drawMirroredAxis(ax, px, ay, py, 'b')
        plt.text(x + 0.5, -y - 0.5, 'XY: (' + str(x) + '; ' + str(y) + ')')

        #draw rotated axis by passed theta
       # r_ax, r_px, r_ay, r_py = rotateMirroredAxis(ax, px, ay, py, theta)
        #drawMirroredAxis(r_ax, r_px, r_ay, r_py, 'k--')

        #r_x, r_y = transformPointToRotatedAxis_Mirrored(x, y, theta)
        #plt.text(x + 2, -y - 2, 'XY_1: (' + str(r_x) + '; ' + str(r_y) + ')')

        #Draw the rectangle representing the sprite and the lines that
        #show its position regions - front, flanks and rear.
        #Next create function which checks to which area the passed
        #point x, y belongs - front, flank, rear based on the angle
        #property that was passed - theta
        #TODO
        drawSpriteRectangle(0, -y, x, y)
        drawSpriteAreasAndBorders(ax, px, ay, py, x, y, theta)
        # checkRegion(0, 0, x, y, theta)
        # checkRegion(15, 15, x, y, theta)
        # checkRegion(5, 20, x, y, theta)
        # checkRegion(-5, 15, x, y, theta)
        for i in range(20):
            checkRegion(-(x / 2), (y * 1.5) - (i * 2), x, y, theta)
            checkRegion(x * 1.5, (y * 1.5) - (i * 2), x, y, theta)
            checkRegion(-x * 1.5 + (i * 2), -(x / 2), x, y, theta)
            checkRegion(-x * 1.5 + (i * 2), y * 1.5, x, y, theta)
        plt.show()
