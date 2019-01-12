//
//  model_loader.hpp
//  project03
//
//  Created by weipingw on 2019/1/12.
//  Copyright © 2019 weipingw. All rights reserved.
//

#ifndef model_loader_hpp
#define model_loader_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
using namespace std;

class ObjLoader{
    
public:
    
    ObjLoader(string filename);
    void Draw();
    
private:
    
    vector<vector<GLfloat>>vSets;
    vector<vector<GLint>>fSets;
    GLuint textureID;
};
#endif /* model_loader_hpp */
