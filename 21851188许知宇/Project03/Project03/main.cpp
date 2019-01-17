//
//  main.cpp
//  Project03
//
//  Created by wxaaaa on 2019/1/7.
//  Copyright © 2019 wxaaaa. All rights reserved.
//
#include "OBJ_Loader.h"
#include <GLUT/GLUT.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;
class ObjLoader{
private:
    vector<vector<GLfloat>> vSets;//存放顶点(x,y,z)坐标
    vector<vector<GLint>> fSets;//存放面的三个顶点索引
    
public:
    ObjLoader(string filename)//构造函数
    {
        string line;
        fstream f;
        f.open(filename, ios::in);
        if (!f.is_open()){
            cout << "Something Went Wrong When Opening Objfiles" << endl;
        }
        
        while (!f.eof()){
            getline(f, line);//拿到obj文件中一行，作为一个字符串
            vector<string>parameters;
            string tailMark = " ";
            string ans = "";
            
            line = line.append(tailMark);
            for (int i = 0; i < line.length(); i++) {
                char ch = line[i];
                if (ch != ' ') {
                    ans+=ch;
                }
                else {
                    parameters.push_back(ans); //取出字符串中的元素，以空格切分
                    ans = "";
                }
            }
            //cout << parameters.size() << endl;
            if (parameters.size() != 4) {
                cout << "the size is not correct" << endl;
            }
            else {
                if (parameters[0] == "v") {   //如果是顶点的话
                    vector<GLfloat>Point;
                    for (int i = 1; i < 4; i++) {   //从1开始，将顶点的xyz三个坐标放入顶点vector
                        GLfloat xyz = atof(parameters[i].c_str());
                        Point.push_back(xyz);
                    }
                    vSets.push_back(Point);
                }
                
                else if (parameters[0] == "f") {   //如果是面的话，存放三个顶点的索引
                    vector<GLint>vIndexSets;
                    for (int i = 1; i < 4; i++){
                        string x = parameters[i];
                        string ans = "";
                        for (int j = 0; j < x.length(); j++) {   //跳过‘/’
                            char ch = x[j];
                            if (ch != '/') {
                                ans += ch;
                            }
                            else {
                                break;
                            }
                        }
                        GLint index = atof(ans.c_str());
                        index = index-1;//因为顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
                        vIndexSets.push_back(index);
                    }
                    fSets.push_back(vIndexSets);
                }
            }
        }
        f.close();
    }
    void Draw()//绘制函数
    {
        
        glBegin(GL_TRIANGLES);//开始绘制
        for (int i = 0; i < fSets.size(); i++) {
            GLfloat VN[3];
            //三个顶点
            GLfloat SV1[3];
            GLfloat SV2[3];
            GLfloat SV3[3];
            
            if ((fSets[i]).size() != 3) {
                cout << "the fSetsets_Size is not correct" << endl;
            }
            else {
                GLint firstVertexIndex = (fSets[i])[0];//取出顶点索引
                GLint secondVertexIndex = (fSets[i])[1];
                GLint thirdVertexIndex = (fSets[i])[2];
                
                SV1[0] = (vSets[firstVertexIndex])[0];//第一个顶点
                SV1[1] = (vSets[firstVertexIndex])[1];
                SV1[2] = (vSets[firstVertexIndex])[2];
                
                SV2[0] = (vSets[secondVertexIndex])[0]; //第二个顶点
                SV2[1] = (vSets[secondVertexIndex])[1];
                SV2[2] = (vSets[secondVertexIndex])[2];
                
                SV3[0] = (vSets[thirdVertexIndex])[0]; //第三个顶点
                SV3[1] = (vSets[thirdVertexIndex])[1];
                SV3[2] = (vSets[thirdVertexIndex])[2];
                
                
                GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
                //(x2-x1,y2-y1,z2-z1)
                vec1[0] = SV1[0] - SV2[0];
                vec1[1] = SV1[1] - SV2[1];
                vec1[2] = SV1[2] - SV2[2];
                
                //(x3-x2,y3-y2,z3-z2)
                vec2[0] = SV1[0] - SV3[0];
                vec2[1] = SV1[1] - SV3[1];
                vec2[2] = SV1[2] - SV3[2];
                
                //(x3-x1,y3-y1,z3-z1)
                vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
                vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
                vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];
                
                GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));
                
                VN[0] = vec3[0] / D;
                VN[1] = vec3[1] / D;
                VN[2] = vec3[2] / D;
                
                glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量
                
                glVertex3f(SV1[0], SV1[1], SV1[2]);//绘制三角面片
                glVertex3f(SV2[0], SV2[1], SV2[2]);
                glVertex3f(SV3[0], SV3[1], SV3[2]);
            }
        }
        glEnd();
    }
};




//模型路
string filePath1 = "bunny.obj";
string filePath2 = "cow.obj";
//
ObjLoader objModel(filePath1);
ObjLoader objMode2(filePath2);

double pitch =0, yaw =0;
int mouse_button;
double mouse_x, mouse_y;
double fovy=45, near=0, far=1000;
double lookx = 0, looky = 0, dist = -500;


double g_dAngle= 0.0f;


void Init(void)
{
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glEnable(GL_TEXTURE_2D);
    
//    if (!LoadTexture())
//    {
//        exit(0);
//    }
    
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 1.0, 1.0, 0.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };
    GLfloat position2[] = { 1000.0, 500.0, 1000.0, 1.0 };
    
    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, position2);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}


void Display(void)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glLoadIdentity();
    glTranslated(lookx,looky,dist);
    
    glRotated(pitch, 1,0,0);
    glRotated(yaw,0,1,0);
    
    glPushMatrix();
    glColor3f(0.6f,0.4f,0.5f);
    //draw a square
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glBegin( GL_QUADS);
     
    glVertex3f(1000.0f, -240.0f, 1000.0f);
    glVertex3f(-1000.0f, -240.0f, 1000.0f);
    glVertex3f(-1000.0f, -240.0f, -1000.0f);
    glVertex3f(1000.0f, -240.0f, -1000.0f);
    
     glEnd();
    
    glPopMatrix();
    glColor3f(1.0f,0.0f,0.0f);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    objModel.Draw();//绘制obj模型
    
    glColor3f(0.0f,1.0f,0.5f);
    glTranslated(300.0f, -100.0f, 300.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    objMode2.Draw();//绘制obj模型
    
     glFlush();
     glutSwapBuffers(); //双缓冲
    
}
void Reshape(int w,int h)
{
    
     glViewport(0,0,(GLsizei)w,(GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     
     gluPerspective( 90.0f, (GLfloat)w/ (GLfloat)h, 0.1f, 1000.0f );
    
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

//void OnTimer( int iTimerIndex)
//{
//     //更新角度
//     g_dAngle += 2.0f;
//     if ( g_dAngle > 360.0f)
//         {
//            g_dAngle -= 360.0f;
//             }
//
//     glutPostRedisplay();//刷新显示
//    glutTimerFunc( 50, OnTimer, 0);
//
//}
//

void Keyboard(unsigned char key, int x, int y)
{
    
     switch (key)
    {
            case 'w': //前
            dist += 10;
            break;
            case 's': //后
            dist -= 10;
            break;
            case 'a': //左
            lookx += 10;
            break;
            case 'd': //右
            lookx -= 10;
            break;
            case 'q': //上
            looky -= 10;
            break;
            case 'e': // 下
            looky += 10;
            break;
            case 'f': //放大
            dist *= 1.5;
            break;
            case 'b': // 缩小
            dist /= 1.5;
            break;
            case 27:
            exit(0);
            break;
        }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    mouse_button = button;
    mouse_x = x;
    mouse_y = y;
}

void motion(int x, int y){
    switch(mouse_button){
        case GLUT_LEFT_BUTTON:
            cout<<"GLUT_LEFT_BUTTON"<<endl;
            if( x==mouse_x && y==mouse_y ) return;
            yaw -= (GLfloat)( x - mouse_x ) /10.0;
            pitch -= (GLfloat)( y - mouse_y ) /10.0;
            break;
        case GLUT_RIGHT_BUTTON:
            cout<<"GLUT_RIGHT_BUTTON"<<endl;
            if( y==mouse_y ) return;
            if( y < mouse_y ) dist += (GLfloat)(mouse_y - y);
            else dist -= (GLfloat)(y - mouse_y);
            if( -dist < near ) dist = -near;
            if( -dist > far ) dist = -far;
            break;
    }
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
    
    
}
 
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(450,450);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Project03");
    Init();
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc( Display);
    glutReshapeFunc( Reshape);
    
    glutMainLoop();
    return 0;
}
