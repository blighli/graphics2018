from OpenGL.GL import *


class ObjLoader(object):
    def __init__(self, fileName):
        self.vertices = list()
        self.faces = list()
        try:
            file = open(fileName)
            for line in file:
                if line.startswith('v '):
                    line = line.strip().split()
                    vertex = (float(line[1]), float(line[2]), float(line[3]))
                    vertex = (round(vertex[0], 2), round(
                        vertex[1], 2), round(vertex[2], 2))
                    self.vertices.append(vertex)

                elif line.startswith('f'):
                    line = line.strip().split()
                    face = (int(line[1]), int(line[2]), int(line[3]))
                    self.faces.append(face)

            file.close()
        except IOError:
            print(fileName + " file not found.")

    def render_scene(self):
        if len(self.faces) > 0:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
            glBegin(GL_TRIANGLES)
            for face in self.faces:
                for f in face:
                    vertexDraw = self.vertices[int(f) - 1]
                    glVertex3fv(vertexDraw)
            glEnd()
