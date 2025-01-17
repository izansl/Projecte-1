#include "Enemy_RedBat.h"
#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Gameplay/scenelevel1.h"
#include "../../Modules/Core/ModuleRender.h"
#include"../../Modules/Core/ModuleTextures.h"
#include"../../Modules/Core/ModuleAudio.h"

Enemy_RedBat::Enemy_RedBat(int x, int y, int wave) : Enemy(x, y) {
	texture = App->textures->Load(FI_spriteEnemy_boss.c_str());
	fly.PushBack({ 0, 344, 156, 156});
	fly.PushBack({ 158, 344, 156, 156});
	fly.PushBack({ 310, 344, 156, 156 });
	fly.PushBack({ 466, 344, 156, 156 });
	currentAnim = &fly;
	fly.speed = 0.2;
	fly.loop = false;

	path.PushBack({ 0, (float)App->sceneLevel_1->velocitatNivell +7 }, 250);
	path.PushBack({ 5, (float)App->sceneLevel_1->velocitatNivell +7 }, 250);


	collider = App->collisions->AddCollider({ 0, 0,158, 158 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBat::Update() {
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
//
void Enemy_RedBat::OnCollision(Collider* c1) {
	fly.PushBack({ 591, 205, 156, 156 });
	fly.PushBack({ 758, 207, 156, 156});
	fly.PushBack({ 962, 205, 156, 156 });
	fly.PushBack({ 10000, 10000, 156, 156 });

	currentAnim = &fly;
	fly.speed = 0.2;
	fly.loop = false;
	App->audio->PlayFx(destroyedFx);
	App->player->score += 50;
}