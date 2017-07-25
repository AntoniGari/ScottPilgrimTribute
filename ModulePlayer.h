#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "Point.h"
#include "SDL/include/SDL_render.h"

struct SDL_Texture;
struct Collider;
struct Particle;

class ModulePlayer : public Module {

enum character_state {
	NONE,
	MOVE,
	ATTACK,
	JUMP
};

public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	void CheckInput();

public:
	SDL_Texture* graphics = nullptr;
	Collider* collider = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation walk;
	Animation run;
	Animation light_punch;


	character_state state;
	Timer* attack_timer;
	
	Particle dust;
	//Particle coin;
	bool finished = false;
	SDL_RendererFlip flip;
	iPoint position;

public:
		
};

#endif // __MODULEPLAYER_H__