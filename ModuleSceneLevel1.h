#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct Collider;

class ModuleSceneLevel1 : public Module {
public:
	ModuleSceneLevel1(bool start_enabled = true);
	~ModuleSceneLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* background;
	SDL_Texture* stars;
};