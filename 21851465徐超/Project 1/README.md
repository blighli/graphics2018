# Project 1

基于原生GLUT框架绘制的茶壶，通过鼠标拖拽实现视角切换，通过键盘上下键改变观察距离

## 环境
macOS Mojave 10.14.1、Xcode 10.1、macOS原生OpenGL.framework、macOS原生GLUT.framework

## 问题
在macOS Mojave、Xcode 10环境下必须调用glutReshapeWindow，并且参数必须与glutInitWindowSize不同，否则会出现黑屏什么都不显示的问题
`
void display() {
    glutReshapeWindow(windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX), viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireTeapot(0.5);
    glutSwapBuffers();
}
`
参见：[Mac Mojave + opengl](https://stackoverflow.com/questions/52509427/mac-mojave-opengl)

## 演示
![Project 1](https://github.com/HanyuXu/graphics2018/blob/master/21851465徐超/Project%201/Project%201.gif)
