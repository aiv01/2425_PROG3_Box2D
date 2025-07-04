#include "physics/BoxCollider2D.h"
#include "physics/RigidBody2D.h"
#include <box2d/box2d.h>
#include "physics/Physics2D.h"
#include "ServiceRegistry.h"
#include "Quad.h"

BoxCollider2D::BoxCollider2D(Quad* InQuad)
    : BoxCollider2D(InQuad, {}) { }

BoxCollider2D::BoxCollider2D(Quad* InQuad, CollisionCallback InCallback)
    : Object(InQuad), UserData(InCallback)
{
    UserData.Object = Object;

    if (!Object->RigidBody) 
    {
        //1. Create Body in the Physics World
        b2BodyDef BodyDef;
        BodyDef.type = b2BodyType::b2_staticBody;
        BodyDef.position.Set(InQuad->Position.x, InQuad->Position.y);

        Physics2D* Physics = ServiceRegistry::GetInstance().GetPhysics();
        Body = Physics->CreateBody(&BodyDef);
    }
    else 
    {
        Body = Object->RigidBody->Body;
    }

    //2. At least one fixture per Body
    glm::vec3 bSize = InQuad->Scale;
    bSize *= 0.5f;

    b2PolygonShape box;
    //box.SetAsBox(bSize.x, bSize.y);
    box.SetAsBox(bSize.x - box.m_radius, bSize.y - box.m_radius);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.isSensor = false;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&UserData);
    
    Fixture = Body->CreateFixture(&fixtureDef);
}