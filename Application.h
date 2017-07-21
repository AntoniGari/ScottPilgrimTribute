#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleParticles;
class ModuleCollision;
class ModuleSceneIntro;
class ModuleSceneLevel1;

class Application {
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleCollision* collision;

	// Game logic --
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModuleSceneLevel1* scene_level1;

private:

	std::list<Module*> modules;
	Module* first_scene = nullptr;
};

extern Application* App;

#endif // __APPLICATION_CPP__