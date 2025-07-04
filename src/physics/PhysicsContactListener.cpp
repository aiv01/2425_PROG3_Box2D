#include "physics/PhysicsContactListener.h"

void PhysicsContactListener::BeginContact(b2Contact* InContact)
{
    b2FixtureUserData& FixtA = InContact->GetFixtureA()->GetUserData();
    b2FixtureUserData& FixtB = InContact->GetFixtureB()->GetUserData();

    if (FixtA.pointer == 0 || FixtB.pointer == 0) {
        return;
    }

    CollisionCallback* CbA = reinterpret_cast<CollisionCallback*>(FixtA.pointer);
    CollisionCallback* CbB = reinterpret_cast<CollisionCallback*>(FixtB.pointer);

    CbA->OnEnter(CbB->Object);
    CbB->OnEnter(CbA->Object);
}

void PhysicsContactListener::EndContact(b2Contact* InContact)
{
    b2FixtureUserData& FixtA = InContact->GetFixtureA()->GetUserData();
    b2FixtureUserData& FixtB = InContact->GetFixtureB()->GetUserData();

    if (FixtA.pointer == 0 || FixtB.pointer == 0) {
        return;
    }

    CollisionCallback* CbA = reinterpret_cast<CollisionCallback*>(FixtA.pointer);
    CollisionCallback* CbB = reinterpret_cast<CollisionCallback*>(FixtB.pointer);

    CbA->OnExit(CbB->Object);
    CbB->OnExit(CbA->Object);
}