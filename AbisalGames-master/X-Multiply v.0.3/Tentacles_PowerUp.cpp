#include "Application.h"
#include "Tentacles_PowerUp.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"


Tentacles_PowerUp::Tentacles_PowerUp(int x, int y) : Enemy(x, y)
{
	tentacleanim.PushBack({ 404, 41, 18,15 });
	tentacleanim.speed = 0.1f;
	animation = &tentacleanim;
	collider = App->collision->AddCollider({0,0,18,15}, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);
	original_y = y;
	powerup_sound = App->audio->LoadSoundEffect("Audio_Assets/power_up2.wav");
}


void Tentacles_PowerUp::OnCollision(Collider* collider)
{
	App->player->tentacles = true;
	App->audio->PlaySoundEffect(powerup_sound);
}

void Tentacles_PowerUp::Move()
{
	position.y = int(float(original_y));
	if (App->enemies->lett == false)
	{
		position.x -= 1;
	}
	else
	{
		position.x -= 0;
	}
}

bool  Tentacles_PowerUp::CleanUp()
{
	LOG("Unload power up audio");
	App->audio->UnloadSoundEffect(powerup_sound);
	powerup_sound = nullptr;
	return true;
}