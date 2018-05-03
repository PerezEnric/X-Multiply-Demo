#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// Template for a new particle "explosion_shot"
	explosion_shot.anim.PushBack({ 33, 36, 7, 8 });
	explosion_shot.anim.PushBack({ 49, 34, 12, 12 });
	explosion_shot.anim.loop = false;
	explosion_shot.anim.speed = 0.2f;

	// Template for a new particle "laser"
	laser.anim.PushBack({ 64, 39, 16, 3 });
	laser.anim.loop = false;
	laser.anim.speed = 0.3f;
	laser.speed.x = 10;
	laser.life = 600;

	// Template for a new particle "explosion"
	explosion.anim.PushBack({ 0, 160, 24, 23 });
	explosion.anim.PushBack({ 3, 201, 26, 22 });
	explosion.anim.PushBack({ 35, 201, 26, 22 });
	explosion.anim.PushBack({ 66, 196, 44, 32 });
	explosion.anim.PushBack({ 117, 197, 37, 28 });
	explosion.anim.PushBack({ 162, 197, 42, 31 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	// Template for a new particle "turbo"

	speedpowerup.anim.PushBack({ 139, 145, 18, 14 });
	speedpowerup.anim.PushBack({ 165, 145, 24, 13 });
	speedpowerup.anim.PushBack({ 194, 146, 42, 11 });
	speedpowerup.anim.PushBack({ 165, 145, 24, 13 });
	speedpowerup.anim.PushBack({ 194, 146, 42, 11 });
	speedpowerup.anim.PushBack({ 165, 145, 24, 13 });
	speedpowerup.anim.PushBack({ 194, 146, 42, 11 });
	speedpowerup.anim.loop = false;
	speedpowerup.anim.speed = 0.2f;

	//Enemy shot

	enemy_shot.anim.PushBack({ 47,166,8,8 });
	enemy_shot.anim.PushBack({ 64,166,8,8 });
	enemy_shot.anim.PushBack({ 47,181,8,8 });
	enemy_shot.anim.PushBack({ 64,181,8,8 });
	enemy_shot.anim.speed = 0.5f;
	enemy_shot.life = 3000;

	//Bomb Power Up
	bombPU.anim.PushBack({ 92, 177, 15, 4 });
	bombPU.anim.PushBack({ 117, 176, 14, 8 });
	bombPU.anim.PushBack({ 143, 172, 12, 12 });
	bombPU.anim.PushBack({ 162, 170, 9 ,14 });
	bombPU.anim.PushBack({ 185, 171, 4, 15 });
	bombPU.anim.loop = false;
	bombPU.anim.speed = 0.2f;
	bombPU.speed = { 2,3 };
	bombPU.life = 1500;

	//explosion player
	explosion_player.anim.PushBack({ 112,144,16,16 });
	explosion_player.anim.PushBack({ 96,144,16,16 });
	explosion_player.anim.PushBack({ 80,144,16,16 });
	explosion_player.anim.PushBack({ 64,144,16,16 });
	explosion_player.anim.PushBack({ 48,144,16,16 });
	explosion_player.anim.PushBack({ 32,144,16,16 });
	explosion_player.anim.PushBack({ 16,144,16,16 });
	explosion_player.anim.PushBack({ 0,144,16,16 });
	explosion_player.anim.loop = false;
	explosion_player.anim.speed = 0.5f;

	//tentacles
	tentacle1 = {6,19,4,11};
	tentacle2 = { 21,19,7,10 };
	tentacle3 = { 36,20,9,8 };
	tentacle4 = { 51,21,10,6 };
	tentacle5 = { 67,22,11,4 };
	tentacle6 = { 186,35,7,10 };
	tentacle7 = { 200,36,9,8 };
	tentacle8 = { 215,37,10,6 };
	tentacle2_back = { 208,55,10,6 };
	tentacle3_back = {224,54,9,8};
	tentacle4_back = {241,53,7,10};
	tentacle5_back = { 212,96,11,4 };
	tentacle6_back = {221,77,10,6};
	tentacle7_back = {227,76,9,8};
	tentacle8_back = {243,75,7,10};
	tentaclehand = { 90,18,19,9 };

}

ModuleParticles::~ModuleParticles()
{
}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Sprites_Assets/Player.png");
	
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
				
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}


Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


	return ret;
}