#pragma once
#include "physics/PhysicsContactListener.h"

class BoxCollider2D 
{
public:
    BoxCollider2D(class Quad* InQuad);
    BoxCollider2D(class Quad* InQuad, CollisionCallback Callback);
private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* Fixture;

    CollisionCallback UserData;

friend class RigidBody2D;
};