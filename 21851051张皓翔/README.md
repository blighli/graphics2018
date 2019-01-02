# 三维动画交互技术课程作业

姓名：张皓翔
学号：21851051



使用的库：

- glfw

- glew

- glm (矩阵计算)

- SOIL (图片加载)

---

**Project01**

  

实现功能：

* 编写了自定义的Shader着色器文件读取方法

* 自己编写并使用了顶点着色器与片元着色器

* 利用以上两个自定义模块渲染了一个立方体（无光照效果与贴图）

* 编写Camera类负责控制摄像机的所有操作（键盘WSAD进行平移、鼠标操作进行旋转）

* 添加了纹理效果

  演示片段：

![image](https://github.com/wszhhx/MyImg/blob/master/project01DEMO.gif?raw=true)



---

**Project02**



实现功能：

- 编写两套着色器，分别渲染太阳（光源）与其他行星。

- 在片元着色器中实现了环境光照效果和漫反射效果

- 自主完成球体顶点的计算和贴图ST坐标的换算已经行星运行轨道的算法

- 为Camera增加了新的功能：锁定星球进行观察

  

  演示片段：

![image](https://github.com/wszhhx/MyImg/blob/master/project02DEMO.gif?raw=true)



![image](https://github.com/wszhhx/MyImg/blob/master/project02DEMO2.gif?raw=true)
