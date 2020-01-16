import numpy as np
import matplotlib.pyplot as plt
import math
import sys


def convertRadian2Degree(alpha):
   return (alpha * 180 / math.pi)

def convertDegree2Radian(beta):
    return (beta * math.pi) / 180

def getInitAxis(x, y):
    ax = np.linspace(-x * 2, x * 2)
    ay = np.linspace(-y * 2, y * 2)

    px = np.zeros(len(ax))
    py = np.zeros(len(ay))

    plt.axis([(ax[0]), (ax[-1] + 1) ,(ay[0]), (ay[-1] + 1)])
    return ax, px, ay, py

def calcAndDrawPolarCoords(x, y):
    R = math.sqrt(pow(x, 2) + pow(y, 2))
    alpha = math.acos(x / R)    
    xp_1 = np.linspace(0, x, 10)
    yp_1 = np.linspace(0, y, 10)
    xp_2 = np.ones(len(yp_1)) * x
    plt.plot(xp_1, yp_1, 'r--')
    plt.plot(xp_2, yp_1, 'r--')
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
    alpha = math.acos(x / R) 
    r_x = R * math.cos(alpha + theta)
    r_y = R * math.sin(alpha + theta)
    return r_x, r_y

#TODO
def checkRegion(x, y):
    return
def drawSpriteRectangle():
    return
def drawSpriteAreasAndBorders():
    return

if len(sys.argv) > 3:
    x = float(sys.argv[1])
    y = float(sys.argv[2])
    theta = convertDegree2Radian(float(sys.argv[3]))
    plt.figure()
    R, alpha, xp_1, xp_2, yp_1 = calcAndDrawPolarCoords(x, y)

    print "x = " + str(x) + " y= " + str(y) + " alpha = " + str(convertRadian2Degree(alpha))

    plt.plot([x], [y], 'ko')

    # ax - x points that draw x axis, px - y points that define y position of each x point, 
    #in initial not rotated is all zeros
    # ay - y points that draw y axis, py - x points that define x position of each y point, 
    #all zeros for not rotated axis
    ax, px, ay, py = getInitAxis(x, y)
    drawAxis(ax, px, ay, py, 'b')
    plt.text(x + 0.5, y + 0.5, 'XY: (' + str(x) + '; ' + str(y) + ')')

    #draw rotated axis by passed theta
    r_ax, r_px, r_ay, r_py = rotateAxis(ax, px, ay, py, theta)
    drawAxis(r_ax, r_px, r_ay, r_py, 'k--')
    
    r_x, r_y = transformPointToRotatedAxis(x, y, theta)
    plt.text(x + 2, y + 2, 'XY_1: (' + str(r_x) + '; ' + str(r_y) + ')')

    #New figure - mirrored coordinates system - reversed y axis -> canvas in qml
    plt.figure()
    plt.axis([(ax[0]), (ax[-1] + 1) ,(ay[0]), (ay[-1] + 1)])
    plt.plot([x], [-y], 'ko')

    drawMirroredAxis(ax, px, ay, py, 'b')
    plt.text(x + 0.5, -y - 0.5, 'XY: (' + str(x) + '; ' + str(y) + ')')

    #draw rotated axis by passed theta
    r_ax, r_px, r_ay, r_py = rotateMirroredAxis(ax, px, ay, py, theta)
    drawMirroredAxis(r_ax, r_px, r_ay, r_py, 'k--')
    
    r_x, r_y = transformPointToRotatedAxis_Mirrored(x, y, theta)
    plt.text(x + 2, -y - 2, 'XY_1: (' + str(r_x) + '; ' + str(r_y) + ')')

    #Draw the rectangle representing the sprite and the lines that
    #show its position regions - front, flanks and rear.
    #Next create function which checks to which area the passed
    #point x, y belongs - front, flank, rear based on the angle
    #property that was passed - theta
    #TODO

    plt.show()
