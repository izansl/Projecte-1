#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"

#include "../../SDLs/SDL/include/SDL.h"

#include "../Modules/Core/ModuleRender.h"
#include "../../../SDLs/SDL_Image/include/SDL_image.h"
#include <iostream>

//#pragma comment( lib, "../../SDLs/SDL/lib/x64/SDL2.lib")
//#pragma comment( lib, "SDL/libx86/SDL2main.lib")


enum class Main_States {
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char* argv[]) {
	ReportMemoryLeaks();

	//SDL_Texture* texture = nullptr;
	//SDL_Surface* surface = IMG_Load("../Assets/Sprites/startScreen.png");

	//if (surface == NULL) {
	//	//LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	//	std::cout << "NOPE" << std::endl;
	//}
	//else {
	//	texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

	//	if (texture == NULL) {
	//		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	//	}
	//}

	int main_return = EXIT_FAILURE;
	Main_States state = Main_States::MAIN_CREATION;

	while (state != Main_States::MAIN_EXIT) {
		switch (state) {
		case Main_States::MAIN_CREATION:
		{
			LOG("Application Creation --------------\n");
			App = new Application();
			state = Main_States::MAIN_START;
		}	break;

		case Main_States::MAIN_START:
		{
			LOG("Application Start --------------\n");
			if (App->Init() == false) {
				LOG("Application Init exits with error -----\n");
				state = Main_States::MAIN_EXIT;
			}
			else {
				state = Main_States::MAIN_UPDATE;
			}
		}	break;

		case Main_States::MAIN_UPDATE:
		{
			Update_Status status = App->Update();

			if (status == Update_Status::UPDATE_ERROR) {
				LOG("Application Update exits with error -----\n");
				state = Main_States::MAIN_EXIT;
			}
			else if (status == Update_Status::UPDATE_STOP) {
				state = Main_States::MAIN_FINISH;
			}
		}	break;

		case Main_States::MAIN_FINISH:
		{
			LOG("Application Finish --------------\n");
			if (App->CleanUp() == true) {
				main_return = EXIT_SUCCESS;
			}
			else {
				LOG("Application CleanUp exits with error -----\n");
			}
			state = Main_States::MAIN_EXIT;
		}
		}
	}

	LOG("\nBye :)\n");

	delete App;

	return main_return;
}