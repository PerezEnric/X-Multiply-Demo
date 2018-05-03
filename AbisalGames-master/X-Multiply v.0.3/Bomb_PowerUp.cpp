#include "Application.h"
#include "Bomb_PowerUp.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"


Bomb_PowerUp::Bomb_PowerUp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 360, 39, 21,16 });
	fly.speed = 0.1f;
	animation = &fly;
	collider = App->collision->AddCollider({ 0, 0, 21, 16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);
	original_y = y;
	powerup_sound = App->audio->LoadSoundEffect("Audio_Assets/power_up2.wav");
}


void Bomb_PowerUp ::OnCollision(Collider* collider)
{
	App->player->bomb = true;
	App->audio->PlaySoundEffect(powerup_sound);
}

void Bomb_PowerUp::Move()
{
	position.y = int(float(original_y));
	if (App->enemies->letb == false)
	{
		position.x -= 1;
	}
	else
	{
		position.x -= 0;
	}
}

bool  Bomb_PowerUp::CleanUp()
{
	LOG("Unload power up audio");
	App->audio->UnloadSoundEffect(powerup_sound);
	powerup_sound = nullptr;
	return true;
}