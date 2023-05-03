#include "Enemy_RedWizard.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Application/FileNames.h"

Enemy_RedWizard::Enemy_RedWizard(int x, int y, int wave, int miem) : Enemy(x, y) {
	texture = App->textures->Load(FI_spriteEnemy_2.c_str());
	
	fly.PushBack({ 4, 22 , 36, 36 });
	fly.PushBack({ 41, 22 ,36, 36 });
	currentAnim = &fly;
	fly.speed = 0.01f;
	fly.loop = true;

	if (wave == 1)
	{
		if (miem == 0)
		{
			path.PushBack({ 0.0, -2.75 }, 520);
			path.PushBack({ 0.0, -8.0 }, 150);
			path.PushBack({ 3, -12.0 }, 650);
		}
	}
	else if (wave == 2)
	{
		if (miem == 0)
		{
			path.PushBack({ 0.0, -2.5}, 580);
			path.PushBack({ 0.0, -8.0 }, 150);
			path.PushBack({ -3, -12.0 }, 650);
		}
	}
	else if (wave == 3)
	{
		if (miem == 0)
		{
			path.PushBack({ 0.0, -2.75}, 680);
			path.PushBack({ 0.0, -8.0 }, 150);
			path.PushBack({ 3, -12.0 }, 650);
		}
	}
	else if (wave == 4)
	{
		if (miem == 0)
		{
			path.PushBack({ 0.0, -2.75 }, 770);
			path.PushBack({ 0.0, -8.0 }, 150);
			path.PushBack({ -3, -12.0 }, 650);
		}
		
	}
	else if (wave == 5)
	{
		if (miem == 0)
		{
			path.PushBack({ 0.0, -2.75 }, 850);
			path.PushBack({ 0.0, -8.0 }, 150);
			path.PushBack({ 3, -12.0 }, 650);
		}
		
	}
	path.PushBack({ 0.0, 0.5 }, 600);
	

	collider = App->collisions->AddCollider({ 0, 0, 36, 36 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedWizard::Update() {
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
