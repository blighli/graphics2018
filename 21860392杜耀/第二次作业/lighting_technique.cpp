
#include "lighting_technique.h"

LightingTechnique::LightingTechnique()
{   
}

bool LightingTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "lighting.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "lighting.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_samplerLocation = GetUniformLocation("gSampler");
    m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Color");
    m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
    m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");

    if (m_dirLightLocation.AmbientIntensity == 0xFFFFFFFF ||
        m_WVPLocation == 0xFFFFFFFF ||
        m_WorldMatrixLocation == 0xFFFFFFFF ||
        m_samplerLocation == 0xFFFFFFFF ||
        m_dirLightLocation.Color == 0xFFFFFFFF ||
        m_dirLightLocation.DiffuseIntensity == 0xFFFFFFFF ||
        m_dirLightLocation.Direction == 0xFFFFFFFF) {
        return false;
    }

    return true;
}

void LightingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}


void LightingTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}


void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_samplerLocation, TextureUnit);
}


void LightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
    Vector3f Direction = Light.Direction;
    Direction.Normalize();
    glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}