#pragma once

class BoxCollider2D 
{
public:
    BoxCollider2D(class Quad* InQuad);

private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* Fixture;
friend class RigidBody2D;
};