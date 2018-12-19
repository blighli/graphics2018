#ifndef GLCAMERA_H
#define GLCAMERA_H
#include "eigen.h"
#include "GL/glu.h"
#include "iostream"

using namespace Eigen;
class GLCamera {
public:
	GLCamera();
	GLCamera(const Vector3d& pos, const Vector3d& target, const Vector3d& up);
	void setModelViewMatrix(); //加载当前MV矩阵

	//设置摄像机视角
	void setShape(float viewAngle, float aspect, float Near, float Far);
	void slide(float du, float dv, float dn);

	//沿三个轴旋转  分别为 N（镜头注视方向），V（镜头上方向量），U(镜头右侧向量）
	void roll(float angle);
	void yaw(float angele);
	void pitch(float angle);
	float getDist();
private:
	Vector3d m_pos;
	Vector3d m_target;
	Vector3d m_up;
	Vector3d u, v, n;
};
#endif // !GLCAMERA_H
