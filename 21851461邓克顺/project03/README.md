# 第三次作业

## 支持两三维模型文件格式

### 1.OBJ

### 2. STL


## 支持多个光源的光照效果

第二次作业 已经实现

## 支持多种视点浏览方式

### 以模型为中心的平移旋转和缩放

第一、二次作业 均已经实现

### 以视点为中心的场景漫游
   关于摄像机漫游其实就是围绕一个函数实现的(通过改变视点以及观察方向来实现)，具体的函数为OpenGL中辅助函数库中的gluLookat()，通过设置相应的参数实现场景的漫游效果。函数如下：  
    void gluLookAt(GLdouble eyex,GLdouble eyey,GLdouble eyez, 
    GLdouble centerx,GLdouble centery,GLdouble centerz, 
    GLdouble upx,GLdouble upy,GLdouble upz);

   [相机漫游-3D-World--参考](https://blog.csdn.net/u010223072/article/details/44620871)
   
   <br>
最终效果
<br>
![效果](https://github.com/AlphaShun/graphics2018/blob/master/21851461%E9%82%93%E5%85%8B%E9%A1%BA/project03/tt.gif)

