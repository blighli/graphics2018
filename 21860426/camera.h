#pragma once
#include<vector>//GL 包含
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>//定义几个可能关于摄像机移动的操作，利用这个抽象的去保存window系统的几种输入
enum Camera_Movement{	 FORWARD,    BACKWARD,    LEFT,    RIGHT};//默认的摄像机的数值
const GLfloat YAW        = -90.0f;//左右移动的角度
const GLfloat PITCH      =  0.0f;//上下移动的角度
const GLfloat SPEED      =  3.0f;//速度
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;//放大
								  //一个抽象的摄像机的类，这个处理输入和计算欧文角度，opengl的向量和矩阵来使用
class Camera{
public:    // Camera Attributes 照相机的属性    
	glm::vec3 Position;//位置    
	glm::vec3 Front;//方向    
	glm::vec3 Up;//上向量    
	glm::vec3 Right;//右向量    
	glm::vec3 WorldUp;//世界坐标的上向量    
    // Eular Angles  欧文角度   
	GLfloat Yaw;//左右的角度    
	GLfloat Pitch;//上下的角度    
    // Camera options 摄像机的操作    
	GLfloat MovementSpeed; //移动的速度    
	GLfloat MouseSensitivity;//鼠标的感应位置   
	GLfloat Zoom;//放大     
   // Constructor with vectors  构建向量    
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)    
	{        
		this->Position = position;        
		this->WorldUp = up;        
		this->Yaw = yaw;        
		this->Pitch = pitch;       
		this->updateCameraVectors(); //更新相机的向量   
	}      
	// Constructor with scalar values  构建标量值    
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)    
	{        
		this->Position = glm::vec3(posX, posY, posZ);        
		this->WorldUp = glm::vec3(upX, upY, upZ);       
		this->Yaw = yaw;        
		
		this->Pitch = pitch;     
		this->updateCameraVectors();    
	}     
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix	//返回通过欧文角度计算的视图矩阵和lookat矩阵 
	glm::mat4 GetViewMatrix()   
	{    

		return glm::lookAt(this->Position, this->Position + this->Front, this->Up);    
	}     // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowingsystems)	
		  //处理输入的按键    
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)    
	{        GLfloat velocity = this->MovementSpeed * deltaTime; //使更新后变化相同       
	if (direction == FORWARD)            
		this->Position += this->Front * velocity;    
	if (direction == BACKWARD)         
		this->Position -= this->Front * velocity;   
	if (direction == LEFT)       
		this->Position -= this->Right * velocity;    
	if (direction == RIGHT)      
		
		
		this->Position += this->Right * velocity;    
	}    
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.	//把鼠标系统输入处理成标准的输入 ，期望x和y的方向，x和y的值被抵消 鼠标控制物体的旋转    
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset,constrainPitch = true)   
	{        
		xoffset *= this->MouseSensitivity;   
		yoffset *= this->MouseSensitivity;   
		this->Yaw   += xoffset; 
		
		this->Pitch += yoffset;  
		// Make sure that when pitch is out of bounds, screen doesn't get flipped		//确定当pitch（倾斜）超过边界屏幕是不过翻转        
		if (constrainPitch)   
		{         
			if (this->Pitch > 89.0f)      
				this->Pitch = 89.0f;       
			
			if (this->Pitch < -89.0f)           
				this->Pitch = -89.0f;    
		}         // Update Front, Right and Up Vectors using the updated Eular angles		//更新前面，右边和上边的向量 用来更新欧文角度  
		this->updateCameraVectors(); 
	}     // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis	//处理输入的放大和缩小，仅要求顶点轴转动  
void ProcessMouseScroll(GLfloat yoffset)    
{
if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)    
this->Zoom -= yoffset;       
if (this->Zoom <= 1.0f)      
this->Zoom = 1.0f;    
if (this->Zoom >= 45.0f) 
this->Zoom = 45.0f;   
} private:    // Calculates the front vector from the Camera's (updated) Eular Angles	//计算方向向量从摄像机更新后的欧文角度   
	void updateCameraVectors()    
	{      
		// Calculate the new Front vector 计算新的方向向量     
		glm::vec3 front;      
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		
		front.y = sin(glm::radians(this->Pitch));     
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));     
		this->Front = glm::normalize(front);        // Also re-calculate the Right and Up vector 重新计算右向量和上向量  
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.    
		this->Up    = glm::normalize(glm::cross(this->Right, this->Front));   
	}
};
