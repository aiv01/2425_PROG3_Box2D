#include <iostream>
#include "OGLWindow.h"
#include "PlatformScene.h"
#include "physics/Physics2D.h"
#include "ServiceRegistry.h"

int main() {
	std::cout << "It' Working" << std::endl;

	OGLWindow* Win = new OGLWindow(800, 600, "OpenGL Window");
	
	float TimeElapsed = 0.f;
	float FixedTimeElapsed = 0.f;

	PlatformScene Scene{*Win};

	float FixedDeltaTime = 0.02f;
	Physics2D Physics{glm::vec2{0, -9.81f}, FixedDeltaTime};

	ServiceRegistry& Registry = ServiceRegistry::GetInstance();
	Registry.SetPhysics(&Physics);

	Scene.Start();
	// till Window is not in closing
	while (Win->IsOpened())
	{
		// update fps 1 sec
		TimeElapsed += Win->GetDeltaTime();
		if (TimeElapsed >= 1.f)
		{
			TimeElapsed -= 1.f;
			int Fps = 1.f / Win->GetDeltaTime();
			char Title[50];
			sprintf_s(Title, sizeof(Title), "OpenGL App | DeltaTime: %f - FPS: %d", Win->GetDeltaTime(), Fps);

			Win->SetTitle(Title);
		}

		FixedTimeElapsed += Win->GetDeltaTime();
		if (FixedTimeElapsed >= FixedDeltaTime) 
		{
			FixedTimeElapsed -= FixedDeltaTime;
			Scene.FixedUpdate();
			Physics.Step();
		}
	
		Scene.Update();
		Win->Update();
	}

	Scene.Destroy();
	delete Win;
	return 0;	
}

