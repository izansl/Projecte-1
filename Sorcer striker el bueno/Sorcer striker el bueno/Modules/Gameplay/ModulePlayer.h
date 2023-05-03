#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "../../Modules/Module.h"
#include "../../Utils/Animation.h"
#include "../../Utils/p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module {

public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	int kills = 0;
	int lives = 3;




public:
	// Position of the player in the map
	iPoint position;	
	
	iPoint backupPosition;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation downAnim;
	Animation upAnim;
	Animation rightAnim;
	Animation leftAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
	
	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

};

#endif //!__MODULE_PLAYER_H__