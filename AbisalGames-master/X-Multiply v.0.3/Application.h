#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 14

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleIntroScene;
class ModuleBackground;
class ModulePlayer;
class ModuleAudio;
class ModuleParticles;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleEnemies;
class ModuleWinLoseScene;
class ModuleFonts;
class Module;

class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleBackground* background = nullptr;
	ModulePlayer* player = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleIntroScene* intro = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleCollision* collision = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleWinLoseScene* win_lose = nullptr;
	ModuleFonts* fonts = nullptr;
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__