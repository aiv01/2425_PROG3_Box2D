#include "OrthoCamera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

OrthoCamera::OrthoCamera(int w, int h, float InOrhoSize) 
{   
    Width = w;
    Height = h;

    auto Pos = glm::vec3(0);
    auto Dir = glm::vec3(0.f, 0.f, -1.f);
    auto Up = glm::vec3(0.f, 1.f, 0.f);
    View = glm::lookAt(Pos, Pos + Dir, Up);


    float Aspect = (float)Width / (float)Height;
    OrthoWidth = InOrhoSize * Aspect;
    OrthoHeight = InOrhoSize;

    float HalfW = OrthoWidth * 0.5;
    float HalfH = OrthoHeight * 0.5;

    float left = -HalfW;
    float right = HalfW;
    float bottom = -HalfH;
    float top = HalfH;
    Proj = glm::ortho(left, right, bottom, top, 0.f, 100.f);

    ViewProj =  Proj * View;
}

glm::mat4 OrthoCamera::GetViewProjMat() const 
{ 
    return ViewProj;
}

int OrthoCamera::GetWidth() const 
{ 
    return Width; 
}

int OrthoCamera::GetHeight() const 
{ 
    return Height; 
}

float OrthoCamera::GetOrthoWidth() const {
    return OrthoWidth;
}

float OrthoCamera::GetOrthoHeight() const {
    return OrthoHeight;
}