#include "physics/Physics2D.h"
#include <box2d/box2d.h>

Physics2D::Physics2D(glm::vec2 InGravity, float InFixedDeltaTime) 
    : Gravity(InGravity), FixedDeltaTime(InFixedDeltaTime)
{
    b2Vec2 BoxGravity{InGravity.x, InGravity.y};
    World = new b2World(BoxGravity);

    World->SetContactListener(&Listener);
}

void Physics2D::Step() {
    World->Step(FixedDeltaTime, 8, 3);
}

b2Body* Physics2D::CreateBody(const b2BodyDef* InDef)
{
    return World->CreateBody(InDef);
}