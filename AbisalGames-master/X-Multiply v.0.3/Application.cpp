#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "ModuleBackground.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleIntroScene.h"
#include "ModuleCollision.h"
#include "ModuleWinLoseScene.h"


Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = fonts = new ModuleFonts();
	modules[5] = audio = new ModuleAudio();
	modules[6] = intro = new ModuleIntroScene();
	modules[7] = background = new ModuleBackground();
	modules[8] = win_lose = new ModuleWinLoseScene();
	modules[9] = enemies = new ModuleEnemies();
	modules[10] = player = new ModulePlayer();
	modules[11] = particles = new ModuleParticles(); 
	modules[12] = collision = new ModuleCollision();
	modules[13] = fade = new ModuleFadeToBlack();

	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable all stopped modules here
	player->Disable();
	background->Disable();
	// ---

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}