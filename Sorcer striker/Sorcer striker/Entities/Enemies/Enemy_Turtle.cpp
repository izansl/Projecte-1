#include "Enemy_Turtle.h"
#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Modules/Gameplay/SceneLevel1.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleRender.h"
#include"../../Modules/Core/ModuleTextures.h"
#include"../../Modules/Core/ModuleAudio.h"

Enemy_Turtle::Enemy_Turtle(int x, int y, int wave) : Enemy(x, y) {
	texture = App->textures->Load(FI_spriteEnemy_enemiesvar_1.c_str());
	fly.PushBack({ 15, 498, 196, 167 });
	fly.PushBack({ 252, 498, 196, 167 });
	fly.PushBack({ 488, 498, 196, 167 });
	fly.PushBack({ 722, 498, 196, 167 });
	fly.PushBack({ 956, 498, 196, 167 });
	fly.PushBack({ 1170, 498, 196, 167 });
	fly.PushBack({ 1380, 498, 196, 167 });
	currentAnim = &fly;
	fly.speed = 0.075;
	fly.loop = false;

	if (wave == 1)
	{
		path.PushBack({ 3, (float)App->sceneLevel_1->velocitatNivell * 0 }, 60);
		path.PushBack({ 0, (float)App->sceneLevel_1->velocitatNivell * 0 }, 200);
	}
	if (wave == 2)
	{
		path.PushBack({ 0, (float)App->sceneLevel_1->velocitatNivell * 0}, 400);
		path.PushBack({ -15, (float)App->sceneLevel_1->velocitatNivell * 0 }, 200);
	}
	

	collider = App->collisions->AddCollider({ 0, 0, 196, 167 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Turtle::Update() {
	
	if (life)
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();
		if (temp >= 120)
		{
			Particle* fireball1 = App->particles->AddParticle(App->particles->minifireshot1, position.x + 98, position.y + 78, Collider::Type::ENEMY, 0);
			Particle* fireball2 = App->particles->AddParticle(App->particles->minifireshot2, position.x + 125, position.y + 69, Collider::Type::ENEMY, 0);
			Particle* fireball3 = App->particles->AddParticle(App->particles->minifireshot3, position.x + 125, position.y + 32, Collider::Type::ENEMY, 0);
			Particle* fireball6 = App->particles->AddParticle(App->particles->minifireshot5, position.x + 98, position.y + 27, Collider::Type::ENEMY, 0);
			Particle* fireball4 = App->particles->AddParticle(App->particles->minifireshot4, position.x + 45, position.y + 32, Collider::Type::ENEMY, 0);
			Particle* fireball5 = App->particles->AddParticle(App->particles->minifireshot6, position.x + 45, position.y + 69, Collider::Type::ENEMY, 0);
			
			
			temp = 0;
		}
		temp++;
	}
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
//
void Enemy_Turtle::OnCollision(Collider* c1) {
	if (life)
	{
		hitcount++;
		if (hitcount < 3)
		{
			damage.PushBack({ 14, 764, 198, 167});
			damage.PushBack({ 252, 498, 196, 167 });
			damage.PushBack({ 490, 764, 198, 167 });
			damage.PushBack({ 722, 498, 196, 167 });
			damage.speed = 0.25f;
			currentAnim = &damage;
			collider = App->collisions->AddCollider({ 0, 0, 196, 167 }, Collider::Type::ENEMY, (Module*)App->enemies);
		}

		else {

			texture = App->textures->Load(FI_spriteEnemy_tank.c_str());
			death.PushBack({ 350, 38, 133, 128 });
			currentAnim = &death;
			death.speed = 0.2;
			death.loop = false;
			App->audio->PlayFx(destroyedFx);
			life = false;
			App->player->score += 400;
		}


	}
}