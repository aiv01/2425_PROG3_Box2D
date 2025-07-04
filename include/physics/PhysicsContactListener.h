#pragma once
#include <box2d/box2d.h>
#include <functional>

class Quad;

struct CollisionCallback 
{
    std::function<void(Quad*)> OnEnter = [](Quad* Obj) { };
    std::function<void(Quad*)> OnExit  = [](Quad* Obj) { };
    Quad* Object = nullptr;
};

class PhysicsContactListener: public b2ContactListener
{
public:
    void BeginContact(b2Contact* InContact);
    void EndContact(b2Contact* InContact);
};
