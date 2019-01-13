#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#include <vector>

// Default camera values
const glm::vec3 WORLDUP = glm::vec3(0.0f, 1.0f, 0.0f);
const float RAD = 3.1415926 / 180;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class CameraModel
{
public:
    // Camera Attributes
    float Radius, U, V;
    glm::vec3 Direction;
    glm::vec3 Position;
    // Camera options
    float MovementSpeed;
    float RadiusSpeed;
    float Zoom;

    // Constructor with vectors
    CameraModel(glm::vec3 direction=glm::vec3(0.0f), float radius=2.0f, float u=0.0f, float v=45.0f) : MovementSpeed(100.0f), RadiusSpeed(0.05f), Zoom(ZOOM)
    {
        Direction = direction;
        Radius = radius;
        U = u;
        V = v;
        upDatePosition();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Direction, WORLDUP);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            V -= velocity;
        if (direction == BACKWARD)
            V += velocity;
        if (direction == LEFT)
            U -= velocity;
        if (direction == RIGHT)
            U += velocity;
        if(V < 5)
            V = 5;
        if(V > 175)
            V = 175;
        if(U < 0)
            U += 360;
        if(U > 360)
            U -= 360;
        upDatePosition();
    }

    void ProcessMouseScroll(float yoffset)
    {
        if (Radius >= 0.2f && Radius <= 10.0f)
            Radius -= yoffset * RadiusSpeed;
        if (Radius <= 0.2f)
            Radius = 0.2f;
        if (Radius >= 10.0f)
            Radius = 10.0f;
        upDatePosition();
    }

private:
    void upDatePosition()
    {
        glm::vec3 dir;
        dir.y = Radius * cos(RAD * V);
        dir.z = Radius * sin(RAD * V) * cos(RAD * U);
        dir.x = Radius * sin(RAD * V) * sin(RAD * U);
        Position = dir + Direction;
    }

};
#endif