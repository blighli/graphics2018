from pygame.locals import *

from scene import *


def Input(scene_obj, panning, detectPos, pos):
    mpb = pygame.mouse.get_pressed() # mouse
    kpb = pygame.key.get_pressed() # keyboard
    msh = pygame.mouse.get_rel() # mouse shift

    if panning==1:
        xterm = scene_obj.xrot - pos[0]
        yterm = scene_obj.yrot - pos[1]
        scene_obj.set_obj_rotation(xterm, yterm, 0.0)

def InputKey(scene_obj, event, w, h):
    mpb = pygame.mouse.get_pressed() # mouse
    kpb = pygame.key.get_pressed() # keyboard
    msh = pygame.mouse.get_rel() # mouse shift

    if kpb[K_SPACE]:
        scene_obj.angleX = 0.0
        scene_obj.angleY = 0.0
        scene_obj.lx = np.sin(scene_obj.angleY)
        scene_obj.ly = np.sin(scene_obj.angleX)
        scene_obj.lz = -np.cos(scene_obj.angleX)

    if kpb[K_q]:
        scene_obj.yrot += 2
    if kpb[K_w]:
        scene_obj.yrot -= 2

    if kpb[K_e]:
        scene_obj.xrot += 2
    if kpb[K_r]:
        scene_obj.xrot -= 2

    if np.rad2deg(scene_obj.angleX) > 90.0:
        scene_obj.angleX = np.deg2rad(90)
    if np.rad2deg(scene_obj.angleX) < -90.0:
        scene_obj.angleX = np.deg2rad(-90)
    if np.rad2deg(scene_obj.angleY) >= 360.0:
        scene_obj.angleY = 0.0
    if np.rad2deg(scene_obj.angleY) <= -360.0:
        scene_obj.angleY = 0.0

    if kpb[K_UP]:
        scene_obj.angleX += 0.005
        scene_obj.ly = np.sin(scene_obj.angleX)
        scene_obj.lz = -np.cos(scene_obj.angleX)
    if kpb[K_DOWN]:
        scene_obj.angleX -= 0.005
        scene_obj.ly = np.sin(scene_obj.angleX)
        scene_obj.lz = -np.cos(scene_obj.angleX)

    if kpb[K_RIGHT]:
        scene_obj.angleY += 0.005
        scene_obj.lx = np.sin(scene_obj.angleY)
        scene_obj.lz = -np.cos(scene_obj.angleY)
    if kpb[K_LEFT]:
        scene_obj.angleY -= 0.005
        scene_obj.lx = np.sin(scene_obj.angleY)
        scene_obj.lz = -np.cos(scene_obj.angleY)

    fraction = 1
    if kpb[K_a]:
        scene_obj.cm_pos[0] += scene_obj.lx * fraction
        scene_obj.cm_pos[2] += scene_obj.lz * fraction
    if kpb[K_s]:
        scene_obj.cm_pos[0] -= scene_obj.lx * fraction
        scene_obj.cm_pos[2] -= scene_obj.lz * fraction

    if kpb[K_z] and event.type == KEYDOWN:
        scene_obj.stopFlag = not scene_obj.stopFlag

    if kpb[K_f]:
        scene_obj.speed += 0.01

    if kpb[K_d]:
        scene_obj.speed -= 0.01

    # limit of speed
    if scene_obj.speed > 1.0:
        scene_obj.speed = 1.0
    if scene_obj.speed < 0.0:
        scene_obj.speed = 0.0

    scene_obj.resize(WIN_SIZE_W, WIN_SIZE_H)

def track_target():
    return
