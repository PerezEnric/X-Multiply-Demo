#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleIntroScene.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"


ModuleBackground::ModuleBackground()
{
	// Background 
	background.x = 54;
	background.y = 492;
	background.w = 4961;
	background.h = 513;



	wall.x = 250;
	wall.y = 1000;
	wall.w = 4961;
	wall.h = 513;

}

bool ModuleBackground::Init()
{

	//Spaceship drop animation
	injectionanim.PushBack({ 28,24,48,102 });
	injectionanim.PushBack({ 107,24,48,105 });
	injectionanim.PushBack({ 188,24,48,103 });
	injectionanim.PushBack({ 266,24,48,113 });
	injectionanim.PushBack({ 335,24,48,121 });
	injectionanim.PushBack({ 414,24,48,123 });
	injectionanim.PushBack({ 414,24,48,122 });
	injectionanim.PushBack({ 335,24,48,120 });
	injectionanim.PushBack({ 266,24,48,112 });
	injectionanim.PushBack({ 188,24,48,103 });
	injectionanim.PushBack({ 107,24,48,105 });
	injectionanim.PushBack({ 28,24,48,102 });

	injectionanim.loop = false;
	injectionanim.speed = 0.2f;

	//Injection Measurements
	injection.x = 28;
	injection.y = 15;
	injection.w = 48;
	injection.h = 102;

	inject = true;

	return true;

}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("Sprites_Assets/TileMap1.png");
	graphicswall = App->textures->Load("Sprites_Assets/FirstLvlMap.png");
	graphicsinjection = App->textures->Load("Sprites_Assets/Injection.png");
	ui = App->textures->Load("Sprites_Assets/UI_1.png");
	firstlvlmusic = App->audio->LoadMusic("Audio_Assets/Stage_1_Music.ogg");
	spaceshipdrop = App->audio->LoadSoundEffect("Audio_Assets/injection.wav");
	App->player->destroyed = false;
	if (App->player->live < 3 && App->player->live > 0)
	{
		App->player->Enable();
		App->player->position.y = 103;
	}
	App->audio->PlayMusic(firstlvlmusic);
	App->audio->PlaySoundEffect(spaceshipdrop);
	App->collision->Enable();
	App->particles->Enable();
	App->enemies->Enable();
	App->textures->Enable();


	//Collider
	App->collision->AddCollider({ 0,213,2800,20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 505, -3,2020,10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 410, 190,50,40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 510, 190,70,40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 500, 190,20,40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 580, 200,20,50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 640, -3,70,25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 760, -3,47,40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1012, -3,96,40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1030, 200,60,30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1150, -3,70,25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1270, 188,80,30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1340, 195,20,30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1460, 135,85,200 }, COLLIDER_WALL);

	//First stretch part
	App->collision->AddCollider({ 1430, 170,50,80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1460, -3,85,95 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1430, -3,50,42 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1445, -3,50,60 }, COLLIDER_WALL);

	App->collision->AddCollider({ 1670, -3,60,25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1790, 185,35,40 }, COLLIDER_WALL);

	//Second stretch part
	App->collision->AddCollider({ 2020, 170,200,50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2030, 150,120,80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2010, 130,140,20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2020, -3,200,42 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2040, 10,120,80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2010, 75,140,20 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2420, -3,100,42 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2550, 190,100,42 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2650, 200,170,42 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2700, 170,85,50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2790, 180,70,50 }, COLLIDER_WALL);


	//Descent
	/*App->collision->AddCollider({2785, 185, 80, 40}, COLLIDER_WALL);
	App->collision->AddCollider({ 2790, 185, 80, 40 }, COLLIDER_WALL);*/
	//DOWN
	App->collision->AddCollider({ 2800, 220, 80, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2840, 250, 80, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2860, 280, 120, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2880, 290, 150, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2900, 300, 140, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2950, 310, 150, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3000, 340, 160, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3050, 370, 170, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3100, 400, 190, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3150, 400, 190, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3175, 425, 250, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3200, 450, 300, 60 }, COLLIDER_WALL);

	//UP
	App->collision->AddCollider({ 2925, 0, 120, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3045, 40, 200, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3170, 65, 200, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3220, 100, 200, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3300, 120, 200, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3350, 150, 200, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3390, 170, 300, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3520, 190, 300, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3600, 200, 300, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3640, 230, 300, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3700, 240, 300, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3720, 260, 250, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3730, 280, 200, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3760, 300, 150, 40 }, COLLIDER_WALL);

	//Final corridor
	//UP
	App->collision->AddCollider({ 3910, 240, 700, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4330, 240, 100, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4520, 240, 100, 100 }, COLLIDER_WALL);

	//DOWN
	App->collision->AddCollider({ 3350, 470, 1500, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3960, 450, 100, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4225, 455, 75, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4350, 455, 40, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4520, 385, 100, 100 }, COLLIDER_WALL);

	//Enemies
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 530, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 540, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 550, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 560, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 570, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 580, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 590, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 530, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 540, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 550, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 560, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 570, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 580, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 590, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 600, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 930, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 940, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 950, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 960, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 970, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 980, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 990, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 1000, 110);	
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 930, 110); 
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 940, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 950, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 960, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 970, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 980, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 990, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL2, 1000, 110);
	

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 630, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 660, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 760, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 760, 135);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 1320, 115);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 1390, 35);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 1390, 70);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3400, 220);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3400, 255);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3470, 255);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3470, 280);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3510, 239);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3600, 260);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3600, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3630, 260);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3630, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3660, 260);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3660, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3690, 260);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3690, 300);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3720, 263);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3720, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3720, 337);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3750, 263);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3750, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3750, 337);

	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 520, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 930, 178);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 1300, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 2290, 178);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 2350, 178);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 2460, 178);

	//Power Ups
	App->enemies->AddEnemy(ENEMY_TYPES::PU, 820, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::SPEEDUP, 820, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::PU, 1010, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::BOMB, 1010, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::PU, 1040, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::TENTACLES, 1043, 105);

	return ret;
}
// UnLoad assets
bool ModuleBackground::CleanUp()
{
	LOG("Unloading first level scene scene");

	App->textures->Unload(graphics);
	graphics = nullptr;
	App->textures->Unload(graphicswall);
	graphicswall = nullptr;
	App->textures->Unload(graphicsinjection);
	graphicsinjection = nullptr;
	App->textures->Unload(ui);
	ui = nullptr;
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();
	App->textures->Disable();

	App->audio->UnloadMusic(firstlvlmusic);
	firstlvlmusic = nullptr;
	App->audio->UnloadSoundEffect(spaceshipdrop);
	spaceshipdrop = nullptr;

	return true;
}
// Update: draw background
update_status ModuleBackground::Update()
{
	animinject();
	// Draw everything --------------------------------------
	App->render->Blit(graphicswall, -10, 0, &wall, 1.0f);
	App->render->Blit(graphics, 0, 0, &background, 1.0f);
	App->render->Blit(graphicsinjection, xinject, yinject, &injection, 1.0f);
	App->render->Blit(ui, 0, 220, NULL, 0.0f, false);

	if (App->intro->flag)
	{
		int vspeed = 1;
		if (App->render->camera.x <= -8010
			&& App->render->camera.x >= -10358)
		{
			App->player->limity += 0.33;
			App->render->camera.y -= vspeed;
			//App->player->position.y += 0.33f;
		}

		if (move == false)
		{
			App->render->camera.x = 0;
		}
	}

	if (App->player->live == 0 && App->player->destroyed == true)
	{
		App->fade->FadeToBlack((Module*)App->background, (Module*)App->win_lose);
		Disable();
		App->player->limitx = 15;
		App->player->limity = 0;
		win = false;
	}
	else if (App->player->live > 0 && App->player->destroyed == true)
	{
		App->fade->FadeToBlack((Module*)App->background, (Module*)App->background);
		
		App->player->limitx += 1;
		if (App->render->camera.x <= -8010
			&& App->render->camera.x >= -10358)
				App->player->limity += 0.33;

		win = false;
		if (App->player->position.x < 1000)
		{
			App->render->camera.x = 0;
			App->player->position.x = 87;
			App->player->limitx = 15;
		}
	}
	if (App->player->position.x == 4600 && !win)
	{
		win = true;
		App->fade->FadeToBlack((Module*)App->background, (Module*)App->win_lose);
	}



	return UPDATE_CONTINUE;
}

//Dropping animation creation

void ModuleBackground::animinject()
{
	if (yinject >= -4 && inject)
	{
		if (injectionanim.GetCurrentFrameIndex() == 3)
		{
			App->player->Enable();
			inject = false;
			move = true;
		}
		injection = injectionanim.GetCurrentFrame();
	}
	else
	{
		if (!inject)
		{

			if (injectionanim.Done())
			{
				yinject--;
			}
			else
			{
				injection = injectionanim.GetCurrentFrame();
			}
		}
		else
		{
			yinject++;
		}
	}
}
