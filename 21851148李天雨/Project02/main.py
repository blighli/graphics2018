from pygame.locals import *
from scene import *

import interface

def main(x, y):
    video_flags = OPENGL|DOUBLEBUF
    pygame.init()
    pygame.display.set_mode((x,y), video_flags)
    clock = pygame.time.Clock()

    scene1 = Scene()

    scene1.loadTex()
    scene1.init()

    detect_pos = []
    frames = 0
    ticks = pygame.time.get_ticks()
    running = 1
    panning = 0
    ani = True
    scene1.set_ani_flag(True)
    while ani:
        event = pygame.event.poll()
        scene1.resize(x, y)
        scene1.set_ani_value()
        scene1.draw()
        pygame.display.flip()
        ani = scene1.get_ani_end_flag()

    while running:
        event = pygame.event.poll()
        if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
            running = 0
        elif event.type == pygame.MOUSEBUTTONDOWN and event.button == LEFT:
            print ("左转 (%d, %d)" % event.pos)
            panning = 1
            detect_pos = event.pos
        elif event.type == pygame.MOUSEBUTTONUP and event.button == LEFT:
            print ("右转 (%d, %d)" % event.pos)
            panning = 0
        elif event.type == pygame.MOUSEMOTION and panning == 1:
            interface.Input(scene1, panning, detect_pos, event.pos)
        else:
            interface.InputKey(scene1, event, x, y)

        scene1.draw()

        pygame.display.flip()
        frames = frames+1
        #clock.tick(60)

    print ("fps:  %d" % ((frames*1000)/(pygame.time.get_ticks()-ticks)))


if __name__ == '__main__':
    main(WIN_SIZE_W, WIN_SIZE_H)
