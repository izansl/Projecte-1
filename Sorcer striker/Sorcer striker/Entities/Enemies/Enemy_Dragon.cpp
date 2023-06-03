#include "Enemy_Dragon.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleAudio.h"

Enemy_Dragon::Enemy_Dragon(int x, int y, int wave) : Enemy(x, y) {
	texture = App->textures->Load(FI_spriteEnemy_dragon.c_str());

	fly.PushBack({ 1121, 1503 , 381, 451 });
	fly.PushBack({ 1579, 1503 , 381, 451 });
	fly.PushBack({ 2041, 1503 , 381, 451 });
	fly.PushBack({ 1579, 1503 , 381, 451 });
	fly.PushBack({ 1121, 1503 , 381, 451 });
	fly.PushBack({ 659, 1503 , 381, 451 });
	fly.PushBack({ 201, 1503 , 381, 451 });
	fly.loop = true;
	currentAnim = &fly;
	fly.speed = 0.1f;
	if (wave == 1)
	{
		
			path.PushBack({ 0, -2.5 }, 30);
			path.PushBack({ 0, -8.0 }, 150);
			path.PushBack({ 2, -8.0 }, 10);
			path.PushBack({ 0, -8.0 }, 70);
			path.PushBack({ -0.75, -10.0 }, 50);
			path.PushBack({ 0, -8.0 }, 30);
			path.PushBack({ 0, -3.0 }, 50);
			path.PushBack({ -2, -12.0 }, 400);
	
		

	}
	else if (wave == 2)
	{
		
			
			path.PushBack({ 0, -2.5 }, 30);
			path.PushBack({ 0, -8.0 }, 100);
			path.PushBack({ -2, -8.0 }, 10);
			path.PushBack({ 0, -8.0 }, 50);
			path.PushBack({ 0.75, -10.0 }, 50);
			path.PushBack({ 0, -8.0 }, 10);
			path.PushBack({ 0, -3.0 }, 50);
			path.PushBack({ 1, -12.0 }, 400);
		
	}
	
	

	collider = App->collisions->AddCollider({ 0, 0, 381, 451 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Dragon::Update() {
		
	if (vida)
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();
	}
	
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Dragon::OnCollision(Collider* c1) {	
		
	if (vida)
	{
		hitcount++;
		if (hitcount < 6)
		{
			damage.PushBack({ 1121, 1503 , 381, 451 });
			damage.PushBack({ 1121, 869 , 381, 451 });
			damage.PushBack({ 1579, 1503 , 381, 451 });
			damage.PushBack({ 1579, 869 , 381, 451 });
			damage.PushBack({ 1121, 1503 , 381, 451 });
			damage.PushBack({ 1121, 869 , 381, 451 });
			damage.PushBack({ 659, 1503 , 381, 451 });
			damage.PushBack({ 659, 869 , 381, 451 });
			damage.speed = 0.25f;
			damage.loop = true;
			currentAnim = &damage;
			collider = App->collisions->AddCollider({ 0, 0,481, 451 }, Collider::Type::ENEMY, (Module*)App->enemies);
		}
		else {
			death.PushBack({ 973, 339, 331, 329 });
			death.PushBack({ 1405, 339, 331, 329 });
			death.PushBack({ 1789, 339, 331, 329 });
			death.PushBack({ 973, 339, 331, 329 });
			death.PushBack({ 1405, 339, 331, 329 });
			death.PushBack({ 1789, 339, 331, 329 });
			death.PushBack({ 0, 0, 0, 0 });
			death.speed = 0.3f;
			death.loop = false;
			App->audio->PlayFx(destroyedFx);
			currentAnim = &death;
			vida = false;

		}


	}
	



}
	