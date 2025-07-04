#pragma once
#include <glm/glm.hpp>
#include <box2d/box2d.h>

enum RBodyType 
{
    Static = b2BodyType::b2_staticBody,
    Kinematic = b2BodyType::b2_kinematicBody,
    Dynamic = b2BodyType::b2_dynamicBody,
};

class RigidBody2D {
public:
    RigidBody2D(class Quad* InQuad, RBodyType BodyType);
    void Update();

    void AddForce(glm::vec2 InForce);
    void AddImpulse(glm::vec2 InForce);
    void SetVelocity(glm::vec2 InVelocity);
private:
    class b2Body* Body;
    class b2Fixture* Fixture;
    class Quad* Object;

friend class BoxCollider2D;
};
