from OpenGL.GL import *
import math

class ObjLoader(object):
    def __init__(self, fileName):
        self.vertices = list()
        self.faces = list()
        ##
        try:
            file = open(fileName)
            for line in file:
                if line.startswith('v '):
                    line = line.strip().split()
                    vertex = (float(line[1]), float(line[2]), float(line[3]) )
                    vertex = (round(vertex[0], 2), round(vertex[1], 2), round(vertex[2], 2))
                    self.vertices.append(vertex)

                elif line.startswith('f'):
                    line = line.strip().split()
                    face = (int(line[1]) -1, int(line[2]) -1, int(line[3])-1)
                    ##
                    self.faces.append(face)

            file.close()
        except IOError:
            print(".obj file not found.")



                # def render_scene(self):
    def render_scene(self):
        SV1 = []
        SV2 = []
        SV3 = []
        
        vec1 = []
        vec2 = []
        vec3 = []
        
        VN = []
        
        if len(self.faces) > 0:
            ##
            #glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
            glBegin(GL_TRIANGLES)
            
            #            for face in self.faces:
            #                for f in face:
            #                    vertexDraw = self.vertices[int(f) - 1]
            #                    if int(f) % 3 == 1:
            #                        glColor4f(0.282, 0.239, 0.545, 0.35)
            #                    elif int(f) % 3 == 2:
            #                        glColor4f(0.729, 0.333, 0.827, 0.35)
            #                    else:
            #                        glColor4f(0.545, 0.000, 0.545, 0.35)
            #                    glColor3f(1.0,1.0,0.0)
            #                    glVertex3fv(vertexDraw)
            for i in range(len(self.faces)):
                
                firstVertexIndex = (self.faces[i])[0]
                secondVertexIndex = (self.faces[i])[1]
                thirdVertexIndex = (self.faces[i])[2]
                
                #顶点1
                SV1.insert(0,(self.vertices[firstVertexIndex])[0])
                SV1.insert(1,(self.vertices[firstVertexIndex])[1])
                SV1.insert(2,(self.vertices[firstVertexIndex])[2])
                
                #顶点2
                #print(secondVertexIndex)
                SV2.insert(0,(self.vertices[secondVertexIndex])[0])
                SV2.insert(1,(self.vertices[secondVertexIndex])[1])
                SV2.insert(2,(self.vertices[secondVertexIndex])[2])
                
                #顶点3
                SV3.insert(0,(self.vertices[thirdVertexIndex])[0])
                SV3.insert(1,(self.vertices[thirdVertexIndex])[1])
                SV3.insert(2,(self.vertices[thirdVertexIndex])[2])
                
                #  (x2-x1,y2-y1,z2-z1)
                vec1.insert(0,SV1[0] - SV2[0]);
                vec1.insert(1,SV1[1] - SV2[1]);
                vec1.insert(2,SV1[2] - SV2[2]);
                
                #(x3-x2,y3-y2,z3-z2)
                #                vec2[0] = SV1[0] - SV3[0];
                #                vec2[1] = SV1[1] - SV3[1];
                #                vec2[2] = SV1[2] - SV3[2];
                vec2.insert(0,SV1[0] - SV3[0]);
                vec2.insert(1,SV1[1] - SV3[1]);
                vec2.insert(2,SV1[2] - SV3[2]);
                
                
                #(x3-x1,y3-y1,z3-z1)
                vec3.insert(0,vec1[1] * vec2[2] - vec1[2] * vec2[1]);
                vec3.insert(1,vec2[0] * vec1[2] - vec2[2] * vec1[0]);
                vec3.insert(2,vec2[1] * vec1[0] - vec2[0] * vec1[1]);
                
                D = math.sqrt(math.pow(vec3[0], 2) + math.pow(vec3[1], 2) + math.pow(vec3[2], 2));
                if (D == 0.0):
                    print(i)
                    continue
            
                VN.insert(0,vec3[0] / D);
                VN.insert(1,vec3[1] / D);
                VN.insert(2,vec3[2] / D);
                
                glNormal3f(VN[0], VN[1], VN[2]);#绘制法向量
                
                glVertex3f(SV1[0], SV1[1], SV1[2]);#绘制三角面片
                glVertex3f(SV2[0], SV2[1], SV2[2]);
                glVertex3f(SV3[0], SV3[1], SV3[2]);
        glEnd()

