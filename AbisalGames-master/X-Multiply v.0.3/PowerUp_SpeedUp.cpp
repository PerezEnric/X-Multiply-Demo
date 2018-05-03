#include "Application.h"
#include "PowerUp_SpeedUp.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"


PowerUp_SpeedUp::PowerUp_SpeedUp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 325, 37, 24,13 });
	fly.speed = 0.1f;
	animation = &fly;
	collider = App->collision->AddCollider({ 0, 0, 24, 13 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);
	original_y = y;
	boost_sound = App->audio->LoadSoundEffect("Audio_Assets/power_up.wav");
}
void PowerUp_SpeedUp::Move()
{
	position.y = int(float(original_y));
	if (App->enemies->lets == false) 
	{	
		position.x -= 1;
	}
	else 
	{
		position.x -= 0;
	}
}

void PowerUp_SpeedUp::OnCollision(Collider* collider)
{
	App->player->turbo = true;
	App->audio->PlaySoundEffect(boost_sound);
}

bool  PowerUp_SpeedUp::CleanUp()
{
	LOG("Unload power up audio");
	App->audio->UnloadSoundEffect(boost_sound);
	boost_sound = nullptr;
	return true;
}