#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleBackground.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleWinLoseScene.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include <stdio.h>



ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 87;
	position.y = 103;

	// idle animation
	idle.PushBack({ 101, 1, 35, 14 });

	idle.speed = 0.2f;

	//upwards animation
	up.PushBack({ 54, 2, 34, 11 });
	up.PushBack({ 6, 4, 35, 12 });
	up.loop = false;
	up.speed = 0.1f;

	//downwards animation

	down.PushBack({ 149, 3, 35, 12 });
	down.PushBack({ 197, 5, 35, 12 });
	down.loop = false;
	down.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	destroyed = false;
	graphics = App->textures->Load("Sprites_Assets/Player.png"); // arcade version
	shot_particle = App->audio->LoadSoundEffect("Audio_Assets/shotp.wav");
	player_death = App->audio->LoadSoundEffect("Audio_Assets/player_death.wav");
	font_score = App->fonts->Load("Sprites_Assets/fonts.png", "0123456789ם.-=יט()ףעבת`´!?abcdefghijklmnopqrstuvwxyz", 2);
	col = App->collision->AddCollider({ position.x, position.y, 35, 14 }, COLLIDER_PLAYER, this);

	return ret;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->audio->UnloadSoundEffect(shot_particle);
	graphics = nullptr;

	shot_particle = nullptr;

	App->audio->UnloadSoundEffect(player_death);

	player_death = nullptr;

	if (col != nullptr)
	{
		col->to_delete = true;
		col = nullptr;
	}

	return true;
}


// Update: draw background
update_status ModulePlayer::Update()
{

	position.x += speed;
	if (App->background->move)
		cameraback += speed;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (turbo == false)
		{
			position.x += (speed * 2);
		}
		else
		{
			position.x += 3;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (turbo == false)
		{
			position.y -= (speed * 2);
		}
		else
		{
			position.y -= 3;
		}

		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (turbo == false)
		{
			position.y += (speed * 2);
		}
		else
		{
			position.y += 3;
		}
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (turbo == false)
		{
			position.x -= (speed * 2);
		}
		else
		{
			position.x -= 3;
		}
	}
	if (tentacles)
	{
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			App->render->Blit(graphics, position.x + 18, position.y, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 14, position.y - 8, &App->particles->tentacle4_back);
			App->render->Blit(graphics, position.x + 6, position.y - 12, &App->particles->tentacle2_back);
			App->render->Blit(graphics, position.x - 3, position.y - 12, &App->particles->tentacle5_back);
			App->render->Blit(graphics, position.x - 12, position.y - 12, &App->particles->tentacle5_back);
			App->render->Blit(graphics, position.x - 21, position.y - 12, &App->particles->tentacle5_back);
			App->render->Blit(graphics, position.x - 30, position.y - 14, &App->particles->tentaclehand);
			//down
			App->render->Blit(graphics, position.x + 18, position.y + 10, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 14, position.y + 18, &App->particles->tentacle8_back);
			App->render->Blit(graphics, position.x + 8, position.y + 22, &App->particles->tentacle7_back);
			App->render->Blit(graphics, position.x - 3, position.y + 28, &App->particles->tentacle5_back);
			App->render->Blit(graphics, position.x - 11, position.y + 28, &App->particles->tentacle5_back);
			App->render->Blit(graphics, position.x - 20, position.y + 28, &App->particles->tentacle5_back);
			App->render->Blit(graphics, position.x - 30, position.y + 25, &App->particles->tentaclehand);
			//animacion hands

			tentacles_front = false;
			tentacles_mid = false;
			tentacles_back = true;
			tentacles_up = false;
			tentacles_down = false;
		}
		else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			App->render->Blit(graphics, position.x + 18, position.y, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 20, position.y - 8, &App->particles->tentacle3);
			App->render->Blit(graphics, position.x + 26, position.y - 12, &App->particles->tentacle4);
			App->render->Blit(graphics, position.x + 33, position.y - 12, &App->particles->tentacle5);
			App->render->Blit(graphics, position.x + 42, position.y - 12, &App->particles->tentacle5);
			App->render->Blit(graphics, position.x + 51, position.y - 12, &App->particles->tentacle5);
			App->render->Blit(graphics, position.x + 52, position.y - 15, &App->particles->tentaclehand);
			//down
			App->render->Blit(graphics, position.x + 18, position.y + 10, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 20, position.y + 18, &App->particles->tentacle6);
			App->render->Blit(graphics, position.x + 24, position.y + 22, &App->particles->tentacle7);
			App->render->Blit(graphics, position.x + 31, position.y + 28, &App->particles->tentacle5);
			App->render->Blit(graphics, position.x + 40, position.y + 28, &App->particles->tentacle5);
			App->render->Blit(graphics, position.x + 49, position.y + 28, &App->particles->tentacle5);
			App->render->Blit(graphics, position.x + 52, position.y + 25, &App->particles->tentaclehand);
			tentacles_front = true;
			tentacles_mid = false;
			tentacles_back = false;
			tentacles_up = false;
			tentacles_down = false;
		}
		else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			App->render->Blit(graphics, position.x + 18, position.y, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 8, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 16, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 24, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 5, position.y - 27, &App->particles->tentaclehand);
			//down
			App->render->Blit(graphics, position.x + 18, position.y + 10, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 18, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 26, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 34, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 42, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 50, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 5, position.y + 53, &App->particles->tentaclehand);
			tentacles_mid = false;
			tentacles_back = false;
			tentacles_front = false;
			tentacles_up = true;
			tentacles_down = false;
		}
		else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			App->render->Blit(graphics, position.x + 18, position.y, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 8, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 16, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 24, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 32, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 40, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 5, position.y - 43, &App->particles->tentaclehand);
			//down
			App->render->Blit(graphics, position.x + 18, position.y + 10, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 18, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 26, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 34, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 5, position.y + 37, &App->particles->tentaclehand);
			tentacles_mid = false;
			tentacles_back = false;
			tentacles_front = false;
			tentacles_up = false;
			tentacles_down = true;
		}
		else
		{
			App->render->Blit(graphics, position.x + 18, position.y, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 8, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 16, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 24, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 32, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y - 40, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 5, position.y - 43, &App->particles->tentaclehand);
			//down
			App->render->Blit(graphics, position.x + 18, position.y + 10, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 18, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 26, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 34, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 42, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 18, position.y + 50, &App->particles->tentacle1);
			App->render->Blit(graphics, position.x + 5, position.y + 53, &App->particles->tentaclehand);
			tentacles_mid = true;
			tentacles_back = false;
			tentacles_front = false;
			tentacles_up = false;
			tentacles_down = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{

		App->particles->AddParticle(App->particles->explosion_shot, position.x + 37, position.y + 1);
		App->particles->AddParticle(App->particles->laser, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT);
		App->audio->PlaySoundEffect(shot_particle);

		if (cd < 5)
		{
			cd++;
		}
		else
		{

			if (bomb)
			{
				App->particles->AddParticle(App->particles->bombPU, position.x, position.y + 7, COLLIDER_PLAYER_SHOT);
			}
			cd = 0;
		}

		if (tentacles && tentacles_front)
		{
			App->particles->AddParticle(App->particles->laser, position.x + 52, position.y - 15, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser, position.x + 52, position.y + 25, COLLIDER_PLAYER_SHOT);
			tentacles_front = false;
		}
		if (tentacles && tentacles_back)
		{
			App->particles->AddParticle(App->particles->laser, position.x -30, position.y - 14, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser, position.x -30, position.y + 25, COLLIDER_PLAYER_SHOT);
			tentacles_back = false;
		}
		if (tentacles && tentacles_mid)
		{
			App->particles->AddParticle(App->particles->laser, position.x + 5, position.y - 43, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser, position.x + 5, position.y + 53, COLLIDER_PLAYER_SHOT);
			tentacles_mid = false;
		}
		if (tentacles && tentacles_up)
		{
			App->particles->AddParticle(App->particles->laser, position.x + 5, position.y - 27, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser, position.x + 5, position.y + 53, COLLIDER_PLAYER_SHOT);
			tentacles_up = false;
		}
		if (tentacles && tentacles_down)
		{
			App->particles->AddParticle(App->particles->laser, position.x + 5, position.y - 43, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser, position.x + 5, position.y + 37, COLLIDER_PLAYER_SHOT);
			tentacles_down = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->background, (Module*)App->win_lose);
		App->background->win = false;

	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->background, (Module*)App->win_lose);
		App->background->win = true;
	}
	//powerup
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN)
	{
		tentacles = !tentacles;
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN)
	{
		bomb = !bomb;
	}
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN)
	{
		turbo = !turbo;
	}

	col->SetPos(position.x, position.y);
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));


	//UI
	score = points;
	sprintf_s(text, 10, "%7d", score);

	App->fonts->BlitText(50, 235, font_score, text);
	//App->fonts->BlitText(32, 150, font_score, "score");

		limitx += 1;
	
	if (position.x < limitx) 
		position.x = limitx;
	if (position.x > limitx + 298)
		position.x = limitx + 298;
	if (position.y < limity) position.y = limity;
	if (position.y > limity + 210) position.y = limity + 210;

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	
	if (c1 == col && destroyed == false && App->fade->IsFading() == false)
	{
		turbo = false;
		destroyed = true;
		live--;
		bomb = false;
		tentacles = false;
		App->audio->PlaySoundEffect(player_death);
		App->particles->AddParticle(App->particles->explosion_player, position.x, position.y, COLLIDER_NONE, 150);
		Disable();
		points = 0;
	}
}
