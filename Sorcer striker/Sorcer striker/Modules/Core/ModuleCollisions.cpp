#include "ModuleCollisions.h"

#include "../../Application/Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "../../../SDLs/SDL/include/SDL_scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled) {

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::CHEST] = true;
	matrix[Collider::Type::WALL][Collider::Type::WALL_PLAYER] = false;
	matrix[Collider::Type::WALL][Collider::Type::POWER_UP] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::CHEST] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL_PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::POWER_UP] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::CHEST] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WALL_PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::POWER_UP] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::CHEST] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL_PLAYER] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::POWER_UP] = false;

	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::ENEMY_SHOOT] = false;
	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::CHEST] = false;
	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::WALL_PLAYER] = false;
	matrix[Collider::Type::ENEMY_SHOOT][Collider::Type::POWER_UP] = false;

	matrix[Collider::Type::CHEST][Collider::Type::WALL] = true;
	matrix[Collider::Type::CHEST][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::CHEST][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::CHEST][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::CHEST][Collider::Type::ENEMY_SHOOT] = false;
	matrix[Collider::Type::CHEST][Collider::Type::CHEST] = false;
	matrix[Collider::Type::CHEST][Collider::Type::WALL_PLAYER] = false;
	matrix[Collider::Type::CHEST][Collider::Type::POWER_UP] = false;

	matrix[Collider::Type::WALL_PLAYER][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL_PLAYER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL_PLAYER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL_PLAYER][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL_PLAYER][Collider::Type::ENEMY_SHOOT] = false;
	matrix[Collider::Type::WALL_PLAYER][Collider::Type::CHEST] = false;
	matrix[Collider::Type::WALL_PLAYER][Collider::Type::WALL_PLAYER] = false;
	matrix[Collider::Type::WALL_PLAYER][Collider::Type::POWER_UP] = false;

	matrix[Collider::Type::POWER_UP][Collider::Type::WALL] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::POWER_UP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::ENEMY_SHOOT] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::CHEST] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::WALL_PLAYER] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::POWER_UP] = false;
}


// Destructor
ModuleCollisions::~ModuleCollisions() {
}

Update_Status ModuleCollisions::PreUpdate() {
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k) {
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect)) {
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr)
						c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr)
						c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update() {
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN || pad.r1==true)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate() {
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw() {
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type) {
		case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha); break;
		case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha); break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha); break;
		case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha); break;
		case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); break;
		case Collider::Type::ENEMY_SHOOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha); break;
		case Collider::Type::WALL_PLAYER: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha); break;
		case Collider::Type::CHEST: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha); break;
		case Collider::Type::POWER_UP: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha); break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp() {
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener) {
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr) {
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider) {
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == collider) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}