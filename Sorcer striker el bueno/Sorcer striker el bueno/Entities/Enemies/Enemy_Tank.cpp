#include "Enemy_Tank.h"
#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleRender.h"
#include"../../Modules/Core/ModuleTextures.h"
#include"../../Modules/Core/ModuleAudio.h"

Enemy_Tank::Enemy_Tank(int x, int y, int wave) : Enemy(x, y) {
	texture = App->textures->Load(FI_spriteEnemy_tank.c_str());
	//movimiento izquierda
	iz.PushBack({ 378, 416, 133, 128 });
	iz.PushBack({ 99, 416, 133, 128 });
	iz.speed = 0.2;
	iz.loop = true;
	//movimiento derecha
	de.PushBack({ 104, 746, 133, 128 });
	de.PushBack({ 363, 746, 133, 128 });
	de.speed = 0.2;
	de.loop = true;
	if (wave == 1)
	{
		path.PushBack({4, -6}, 100, &de);
	}
	else if (wave == 2)
	{
		path.PushBack({ -4, -6 }, 100, &iz);
	}



	collider = App->collisions->AddCollider({ 0, 0,133, 128 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Tank::Update() {
	

	if (life)
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
//
void Enemy_Tank::OnCollision(Collider* c1) {
	if (life)
	{
		hitcount++;
		if (hitcount < 5 )
		{
			damage.PushBack({ 106, 579, 133, 128 });
			damage.PushBack({ 105, 747, 133, 128 });
			damage.speed = 0.25f;
			currentAnim = &damage;
			collider = App->collisions->AddCollider({ 0, 0,133, 128 }, Collider::Type::ENEMY, (Module*)App->enemies);
		}
		
		else {

			death.PushBack({ 350, 38, 133, 128 });
			currentAnim = &death;
			death.speed = 0.2;
			death.loop = false;
			App->audio->PlayFx(destroyedFx);
			life = false;

		}


	}
	
}