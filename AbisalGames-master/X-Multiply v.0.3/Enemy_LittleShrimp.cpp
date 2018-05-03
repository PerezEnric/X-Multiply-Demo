#include "Application.h"
#include "Enemy_LittleShrimp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_LittleShrimp::Enemy_LittleShrimp(int x, int y) : Enemy(x, y)
{
	fly_shrimp.PushBack({ 37, 74, 43, 27 });
	fly_shrimp.PushBack({ 37, 127, 41, 32 });
	fly_shrimp.speed = 0.1f;
	animation = &fly_shrimp;
	collider = App->collision->AddCollider({ 0, 0, 42, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
	shrimp_death = App->audio->LoadSoundEffect("Audio_Assets/Ball_Death.wav");
}
void Enemy_LittleShrimp::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
		{
			going_up = false;
			cd++;
			if (cd > 2)
			{
				App->particles->AddParticle(App->particles->enemy_shot, position.x + 30, position.y + 30, COLLIDER_ENEMY_SHOT);
				App->particles->enemy_shot.speed = { -1,1 };
				cd = 0;
			}
		}
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
	else 
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1.5f;
}

void Enemy_LittleShrimp::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->player->points += points;
	App->audio->PlaySoundEffect(shrimp_death);
}

bool Enemy_LittleShrimp::CleanUp()
{
	LOG("Freeing enemy audio");
	App->audio->UnloadSoundEffect(shrimp_death);
	shrimp_death = nullptr;

	return true;
}