#include <stdlib.h>
#include <windows.h>
#include<GL/glut.h>
// ����������


// ��������İ˸����㱣�浽һ����������

static const float vertex_list[][3] =
{
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
};

// ��Ҫʹ�õĶ������ű��浽һ����������

static const GLint index_list[][2] =
{
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7},
    {0, 2},
    {1, 3},
    {4, 6},
    {5, 7},
    {0, 4},
    {1, 5},
    {7, 3},
    {2, 6}
};

// ����������

void DrawCube(void)
{
    int i,j;

    glBegin(GL_LINES);
    for(i=0; i<12; ++i) // 12 ���߶�

    {
        for(j=0; j<2; ++j) // ÿ���߶� 2������

        {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
}

static float rotate = 0;
static int times = 0;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    //glTranslatef(-0.2, 0, 0); // ƽ��

    //glScalef(2, 1, 1);    // ����


    times++;
    if(times > 100)
    {
        times = 0;
    }

    if(times % 100 == 0)
    {
        rotate += 0.3;
    }

    glRotatef(rotate, 0, 1, 0);
    glRotatef(rotate, 1, 0, 0);

    glColor3f(0, 0, 1);

    DrawCube();

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GLDemo");
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutMainLoop();
    return 0;
}
