#include "physics/RigidBody2D.h"
#include "physics/BoxCollider2D.h"
#include <box2d/box2d.h>
#include "Quad.h"
#include "ServiceRegistry.h"
#include "physics/Physics2D.h"

RigidBody2D::RigidBody2D(Quad* InQuad) 
    : Object(InQuad)
{   

    if (!Object->BoxCollider) 
    {
        //1. Create Body in the Physics World
        b2BodyDef BodyDef;
        BodyDef.type = b2BodyType::b2_dynamicBody;
        BodyDef.position.Set(InQuad->Position.x, InQuad->Position.y);

        Physics2D* Physics = ServiceRegistry::GetInstance().GetPhysics();
        Body = Physics->CreateBody(&BodyDef);
    } 
    else 
    {
        Body = Object->BoxCollider->Body;
        Body->SetType(b2BodyType::b2_dynamicBody);
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
