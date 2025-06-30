#pragma once
#include <glm/glm.hpp>

class Physics2D {

public:
    Physics2D(glm::vec2 InGravity, float InFixedDeltaTime);
    void Step();
    class b2Body* CreateBody(const struct b2BodyDef* InDef);
private:
    glm::vec2 Gravity;
    float FixedDeltaTime;
    class b2World* World;
};