//
//  ObjLoader.hpp
//  Project03
//
//  Created by 钱立清 on 2019/1/8.
//  Copyright © 2019 钱立清. All rights reserved.
//

#include "glew.h"
#include "glut/glut.h"
#include <vector>
#include <string>
using namespace std;
class ObjLoader{
public:
    ObjLoader(string filename);//构造函数
    void Draw();//绘制函数
private:
    vector<vector<GLfloat>>vSets;//存放顶点(x,y,z)坐标
    vector<vector<GLint>>fSets;//存放面的三个顶点索引
};
