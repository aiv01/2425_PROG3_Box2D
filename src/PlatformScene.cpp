#include "PlatformScene.h"
#include "OGLQuadRenderer.h"
#include "OrthoCamera.h"
#include "physics/RigidBody2D.h"
#include "physics/BoxCollider2D.h"
#include <iostream>

void PlatformScene::Start() 
{
    Camera = new OrthoCamera(Win.GetWidth(), Win.GetHeight(), 10.f);

    Quad* Floor = new Quad(Camera->GetOrthoWidth(), 1.f);
    Floor->Name = "Floor";
    Floor->Position = glm::vec3{0, -Camera->GetOrthoHeight() * 0.5f + Floor->Scale.y * 0.5f, 0};
    Floor->BoxCollider = new BoxCollider2D(Floor);

    Player = new Quad(1, 1);
    Player->Name = "Player";
    Player->Position = glm::vec3{0, 0, 0};
    Player->Color = Color_Red;

    CollisionCallback PlayerCb;
    PlayerCb.OnEnter = [](Quad* Object) {
        std::cout << "Player OnEnter: " << Object->Name << "\n";
    };
    PlayerCb.OnExit = [](Quad* Object) {
        std::cout << "Player OnExit: " << Object->Name << "\n";
    };

    Player->BoxCollider = new BoxCollider2D(Player, PlayerCb);
    Player->RigidBody = new RigidBody2D(Player, RBodyType::Dynamic);
    
    Platform = new Quad(3, 1);
    Platform->Name = "Platform";
    Platform->Position = glm::vec3(3, 0, 0);
    Platform->Color = Color_Yellow;
    Platform->RigidBody = new RigidBody2D(Platform, RBodyType::Kinematic);
    Platform->BoxCollider = new BoxCollider2D(Platform);

    Quads.push_back(Floor);    
    Quads.push_back(Player);
    Quads.push_back(Platform);

    SelectedMoveForce = {0, 0};
    SelectedJumpForce = {0, 0};
}

void PlatformScene::Update()
{
    float MoveForce = 10.f;
    float JumpForce = 5.f;

    //Move
    if (Win.IsKeyPressed(Key::KEY_RIGHT))
    {
        //Player->RigidBody->AddForce({MoveForce, 0});
        SelectedMoveForce = {MoveForce, 0};
    } 
    else if (Win.IsKeyPressed(Key::KEY_LEFT))
    {
        //Player->RigidBody->AddForce({-MoveForce, 0});
        SelectedMoveForce = {-MoveForce, 0};
    }

    //Jump
    static bool JumpPressed = false;
    if (!JumpPressed && Win.IsKeyPressed(Key::KEY_UP))
    {
        JumpPressed = true;
        //Player->RigidBody->AddImpulse({0, JumpForce});
        SelectedJumpForce = {0, JumpForce};
    }
    else 
    {
        JumpPressed = Win.IsKeyPressed(Key::KEY_UP);
    }
    
    float Speed = 1.5f;
    float MaxDiff = 2.f;
    static auto PlatformOrigin = Platform->Position;
    auto Diff = Platform->Position - PlatformOrigin;
    static glm::vec2 PlatDir{1, 0};
    if (Diff.x > MaxDiff) 
    {
        PlatDir = {-1, 0};
    } 
    else if (Diff.x < -MaxDiff) 
    {
        PlatDir = {1, 0};
    }

    Platform->RigidBody->SetVelocity(PlatDir * Speed);

    Renderer.Draw(Quads, Camera);
}

 void PlatformScene::FixedUpdate()
 {  

    Player->RigidBody->AddForce(SelectedMoveForce);
    SelectedMoveForce = {0, 0};

    Player->RigidBody->AddImpulse(SelectedJumpForce);
    SelectedJumpForce = {0, 0};

    for(auto* Each: Quads) {
        if (Each->RigidBody) Each->RigidBody->Update();
    }
 }

void PlatformScene::Destroy()
{
    delete Camera;
    for (auto* Each : Quads) delete Each;
}
