#include "physics/RigidBody2D.h"
#include "physics/BoxCollider2D.h"
#include <box2d/box2d.h>
#include "Quad.h"
#include "ServiceRegistry.h"
#include "physics/Physics2D.h"

RigidBody2D::RigidBody2D(Quad* InQuad, RBodyType BodyType) 
    : Object(InQuad)
{   

    if (!Object->BoxCollider) 
    {
        //1. Create Body in the Physics World
        b2BodyDef BodyDef;
        BodyDef.type = static_cast<b2BodyType>(BodyType);
        BodyDef.position.Set(InQuad->Position.x, InQuad->Position.y);

        Physics2D* Physics = ServiceRegistry::GetInstance().GetPhysics();
        Body = Physics->CreateBody(&BodyDef);
    } 
    else 
    {
        Body = Object->BoxCollider->Body;
        Body->SetType(static_cast<b2BodyType>(BodyType));
    }

    //2. At least one fixture per RigidBody
    glm::vec3 bSize = InQuad->Scale;
    bSize *= 0.5f;

    b2PolygonShape box;
    box.SetAsBox(bSize.x, bSize.y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.f;   // Kg/m2 for dynamic body must be > 0.f
    fixtureDef.isSensor = false;

    fixtureDef.filter.categoryBits = 0;  //No collision
    fixtureDef.filter.maskBits = 0;      //No collision

    Fixture = Body->CreateFixture(&fixtureDef);
}

void RigidBody2D::Update() {
    b2Vec2 B2Pos = Body->GetPosition();
    Object->Position.x = B2Pos.x;
    Object->Position.y = B2Pos.y;
}

void RigidBody2D::AddForce(glm::vec2 InForce)
{
    b2Vec2 Force{InForce.x, InForce.y};
    Body->ApplyForceToCenter(Force, true);
}


void RigidBody2D::AddImpulse(glm::vec2 InForce)
{
    b2Vec2 Force{InForce.x, InForce.y};
    Body->ApplyLinearImpulseToCenter(Force, true);
}

void RigidBody2D::SetVelocity(glm::vec2 InVelocity)
{
    b2Vec2 Velocity{InVelocity.x, InVelocity.y};
    Body->SetLinearVelocity(Velocity);
}