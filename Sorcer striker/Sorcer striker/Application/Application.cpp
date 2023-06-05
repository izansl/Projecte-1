#include "Application.h"
#include <iostream>
#include "../../SDLs/SDL/include/SDL.h"

#include "../Modules/Module.h"
#include "../Modules/Core/ModuleWindow.h"
#include "../Modules/Core/ModuleInput.h"
#include "../Modules/Core/ModuleTextures.h"
#include "../Modules/Core/ModuleAudio.h"
#include "../Modules/Core/ModuleParticles.h"
#include "../Modules/Core/ModuleCollisions.h"
#include "../Modules/Core/ModuleFadeToBlack.h"
#include "../Modules/Core/ModuleFonts.h"
#include "../Modules/Core/ModuleRender.h"
#include "../Modules/Core/ModuleHUD.h"
#include "../Modules/Gameplay/ModuleInsertCoin.h"
#include "../Modules/Gameplay/ModulePlayer.h"
#include "../Modules/Gameplay/SceneIntro.h"
#include "../Modules/Gameplay/SceneLevel1.h"
#include "../Modules/Gameplay/SceneLevel1_Foreground.h"
#include "../Modules/Gameplay/SceneStart.h"
#include "../Modules/Gameplay/ScenePantallaLose.h"
#include "../Modules/Gameplay/ModuleEnemies.h"
#include "../Modules/Gameplay/SceneOutro.h"

#include "../Modules/Gameplay/ScenePreintro.h"

int start_time = SDL_GetTicks();
int last_frame_time = start_time;
int frame_counter = 0;
int elapsed_time = 0;
int fps = 0;

Application::Application() {
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules.push_back(window = new ModuleWindow(true));
	modules.push_back(input = new ModuleInput(true));
	modules.push_back(textures = new ModuleTextures(true));
	modules.push_back(audio = new ModuleAudio(true));

	modules.push_back(scenePreintro = new ScenePreintro(true));
	modules.push_back(sceneIntro = new SceneIntro(true));
	modules.push_back(sceneStart = new SceneStart(true));
	modules.push_back(sceneOutro = new SceneOutro(true));
	modules.push_back(sceneLevel_1 = new SceneLevel1(true));
	modules.push_back(sceneLevel_1_foreground = new SceneLevel1_Foreground(true));

	modules.push_back(player = new ModulePlayer(true));
	modules.push_back(enemies = new ModuleEnemies(true));
	modules.push_back(particles = new ModuleParticles(true));
	modules.push_back(collisions = new ModuleCollisions(true));
	modules.push_back(fade = new ModuleFadeToBlack(true));
	modules.push_back(fonts = new ModuleFonts(true));

	modules.push_back(hud = new ModuleHUD(true));
	modules.push_back(insertCoins = new ModuleInsertCoin(true));
	modules.push_back(scenePantallaLose = new ScenePantallaLose(true));

	modules.push_back(render = new ModuleRender(true));

	vectorSize = modules.size();
}

Application::~Application() {
	for (int i = 0; i < vectorSize; ++i) {
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init() {
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < vectorSize && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < vectorSize && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update() {
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < vectorSize && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < vectorSize && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < vectorSize && ret == Update_Status::UPDATE_CONTINUE; ++i)
		// Only paint is Scene1 is eneabled
		if (i == 15)
		{
			if (modules[6]->IsEnabled()) {
				ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;
				ret = modules[7]->PostUpdate();
			}
		}
		else if (i == 17)
		{
			if (modules[5]->IsEnabled()) {
				ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;
			}
		}
		else
			ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;



	// Control the FPS
	elapsed_time = SDL_GetTicks() - last_frame_time;
	if (elapsed_time < 1000 / 60) {
		SDL_Delay(1000 / 60 - elapsed_time);
	}

	frame_counter++;
	if (SDL_GetTicks() - start_time > 1000) {
		fps = frame_counter * 1000 / (SDL_GetTicks() - start_time);
		std::cout << "FPS: " << fps << std::endl;
		start_time = SDL_GetTicks();
		frame_counter = 0;
	}

	last_frame_time = SDL_GetTicks();

	return ret;
}

bool Application::CleanUp() {
	bool ret = true;

	for (int i = vectorSize - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}