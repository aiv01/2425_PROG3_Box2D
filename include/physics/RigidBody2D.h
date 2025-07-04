#pragma once
#include <glm/glm.hpp>
class RigidBody2D {
public:
    RigidBody2D(class Quad* InQuad);
    void Update();

    void AddForce(glm::vec2 InForce);
    void AddImpulse(glm::vec2 InForce);
private:
    class b2Body* Body;
    class b2Fixture* Fixture;
    class Quad* Object;

friend class BoxCollider2D;
};
