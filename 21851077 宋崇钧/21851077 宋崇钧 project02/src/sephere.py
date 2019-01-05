import math
import numpy as np

def radian(angular):
    return math.pi / 180 * angular

def to_XYZ(u, v, r):
    return  r*math.sin(radian(v))*math.cos(radian(u)), \
            r*math.sin(radian(v))*math.sin(radian(u)), \
            r*math.cos(radian(v))

def get_norm(u, v):
    return to_XYZ(u, v, 1)

# 等积投影
def get_tex_coor(u, v):
    x = math.cos(radian(v))
    y = math.sin(radian(v))
    z = math.sqrt(math.pow(x, 2) + math.pow((1-y), 2))
    if v < 90:
        y = 0.5 + z / math.sqrt(2) / 2
    else:
        y = 0.5 - z / math.sqrt(2) / 2 
    return 1-u/360, y

def to_data(t):
    s = ""
    for i in t:
        s = s + str(i)
        s +=" "
    return s


file   = open("sphere.dat", "w")
strip  = 10
radius = 1

file.write(str(strip)+" "+str(strip)+" ")
for v in np.arange(0, 180+strip, strip):
    for u in np.arange(0, 360+strip, strip):
        file.write(to_data(to_XYZ(u, v, radius)))
        file.write(to_data(get_norm(u, v)))
        file.write(to_data(get_tex_coor(u, v)))
print(np.arange(0, 180+strip, strip).size)
print(np.arange(0, 360+strip, strip).size)

file.close()




