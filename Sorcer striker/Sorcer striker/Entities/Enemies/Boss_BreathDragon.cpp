#include "Boss_BreathDragon.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleRender.h"
#include"../../Modules/Core/ModuleTextures.h"


Boss_BreathDragon::Boss_BreathDragon(int x, int y, int wave) : Enemy(x, y) {

	vides[0] = 15; // Cuerpo 0
	vides[1] = 5; // Cabeza 1
	vides[2] = 5; // Cabeza 2
	vides[3] = 5; // Cabeza 2

	texturaBoss = App->textures->Load(FI_spriteEnemy_boss.c_str());

	animationFan.PushBack({ 0, 230, 115, 115 });
	animationFan.PushBack({ 116, 230, 115, 115 });
	animationFan.speed = 0.2;
	animationFan.loop = true;
	pathFan1.PushBack({ 0,0 }, 20, &animationFan);
	pathFan2.PushBack({ 50,0 }, 20, &animationFan);
	pathFan3.PushBack({ 100,0 }, 20, &animationFan);
	pathFan4.PushBack({ 150,0 }, 20, &animationFan);

	animationHead.PushBack({ 0, 502, 180, 180 });
	animationHead.PushBack({ 180 * 2, 502, 180, 180 });
	animationHead.PushBack({ 180 * 4, 502, 180, 180 });
	animationHead.speed = 0.1f;
	animationHead.loop = true;
	pathCabeza1.PushBack({ 0,0 }, 20, &animationHead);
	pathCabeza2.PushBack({ 50,0 }, 20, &animationHead);
	pathCabeza3.PushBack({ 100,0 }, 20, &animationHead);

	animationHeadDamaged.PushBack({ 180 * 1, 502, 180, 180 });
	animationHeadDamaged.PushBack({ 180 * 3, 502, 180, 180 });
	animationHeadDamaged.PushBack({ 180 * 5, 502, 180, 180 });
	animationHeadDamaged.speed = 0.1f;
	animationHeadDamaged.loop = true;

	particleFire.anim.PushBack({ 0, 690, 157, 157 });
	particleFire.anim.PushBack({ 157, 690, 157, 157 });
	particleFire.anim.PushBack({ 157 * 2, 690, 157, 157 });
	particleFire.anim.PushBack({ 157 * 3, 690, 157, 157 });
	particleFire.anim.PushBack({ 157 * 4, 690, 157, 157 });
	particleFire.anim.PushBack({ 157 * 5, 690, 157, 157 });
	particleFire.anim.PushBack({ 157 * 6, 690, 157, 157 });
	particleFire.speed = iPoint(0, -12);
	particleFire.anim.speed = 0.05f;
	particleFire.lifetime = 115;

	//collider = App->collisions->AddCollider({ 0, 0,1200, 400 }, Collider::Type::ENEMY, (Module*)App->enemies);
	//colliderCabeza1 = App->collisions->AddCollider({ 0, 0,180, 180 }, Collider::Type::ENEMY, (Module*)App->enemies);
	//colliderCabeza2 = App->collisions->AddCollider({ 0, 0,180, 180 }, Collider::Type::ENEMY, (Module*)App->enemies);
	//colliderCabeza3 = App->collisions->AddCollider({ 0, 0,180, 180 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Boss_BreathDragon::Update() {

	/*if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));*/


	if (pathFan1.GetCurrentAnimation() != nullptr) {
		pathFan1.Update();
		App->render->Blit(texturaBoss, position.x, position.y, &(pathFan1.GetCurrentAnimation()->GetCurrentFrame()));
	}
	if (pathFan2.GetCurrentAnimation() != nullptr) { 
		pathFan2.Update(); 
		App->render->Blit(texturaBoss, position.x, position.y, &(pathFan2.GetCurrentAnimation()->GetCurrentFrame()));
	}
	if (pathFan3.GetCurrentAnimation() != nullptr) {
		pathFan3.Update();
		App->render->Blit(texturaBoss, position.x, position.y, &(pathFan3.GetCurrentAnimation()->GetCurrentFrame()));
	}
	if (pathFan4.GetCurrentAnimation() != nullptr) {
		pathFan4.Update();
		App->render->Blit(texturaBoss, position.x, position.y, &(pathFan4.GetCurrentAnimation()->GetCurrentFrame()));
	}

	

	//App->render->Blit(texture, position.x, position.y, &(pathFan3.GetCurrentAnimation()->GetCurrentFrame()));
	//App->render->Blit(texture, position.x, position.y, &(pathFan4.GetCurrentAnimation()->GetCurrentFrame()));

	////pathCabeza1.Update();
	////pathCabeza2.Update();
	////pathCabeza3.Update();
	////App->render->Blit(texture, position.x, position.y, &(pathCabeza1.GetCurrentAnimation()->GetCurrentFrame()));
	////App->render->Blit(texture, position.x, position.y, &(pathCabeza2.GetCurrentAnimation()->GetCurrentFrame()));
	////App->render->Blit(texture, position.x, position.y, &(pathCabeza3.GetCurrentAnimation()->GetCurrentFrame()));


	position = spawnPos + pathFan1.GetRelativePosition();
	Enemy::Update();
}

void Boss_BreathDragon::OnCollisionGeneral(Collider* c1) {
	if (c1->type == Collider::Type::PLAYER_SHOT)
	{
		// Si cuerpo tiene 0 vidas muere || las tres cabezas tienen 0 vidas muere
		if ((vides[0] <= 0) || (vides[1] <= 0 && vides[2] <= 0 && vides[3] <= 0))
			this->SetToDelete();
		else
			vides[0] -= 1;
	}
}

void Boss_BreathDragon::OnCollisionHead1(Collider* c1) {
	if (c1->type == Collider::Type::PLAYER_SHOT && !headDestroy) {

		if ((vides[0] <= 0) || (vides[1] <= 0 && vides[2] <= 0 && vides[3] <= 0))
			this->SetToDelete();
		else {
			if (vides[1] <= 0) headDestroy = true;
			else vides[1] -= 1;
		}
	}
}

void Boss_BreathDragon::OnCollisionHead2(Collider* c1) {
	if (c1->type == Collider::Type::PLAYER_SHOT && !headDestroy2) {

		if ((vides[0] <= 0) || (vides[1] <= 0 && vides[2] <= 0 && vides[3] <= 0))
			this->SetToDelete();
		else {
			if (vides[2] <= 0) headDestroy2 = true;
			else vides[2] -= 1;
		}
	}
}

void Boss_BreathDragon::OnCollisionHead3(Collider* c1)
{
	if (c1->type == Collider::Type::PLAYER_SHOT && !headDestroy3) {

		if ((vides[0] <= 0) || (vides[1] <= 0 && vides[2] <= 0 && vides[3] <= 0))
			this->SetToDelete();
		else {
			if (vides[3] <= 0) headDestroy3 = true;
			else vides[3] -= 1;
		}
	}
}
