#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled) {
	// idle animation (just the ship)
	idle.frames.push_back({0, 0, 40, 70});
	idle.frames.push_back({40, 0, 40, 70 });
	idle.frames.push_back({80, 0, 40, 70 });
	idle.frames.push_back({120, 0, 40, 70 });
	idle.frames.push_back({160, 0, 40, 70 });
	idle.frames.push_back({200, 0, 40, 70 });
	idle.frames.push_back({240, 0, 40, 70 });
	idle.frames.push_back({280, 0, 40, 70 });
	idle.loop = true;
	idle.speed = 0.2f;

	//move upwards
	walk.frames.push_back({320, 0, 40, 70 });
	walk.frames.push_back({360, 0, 40, 70 });
	walk.frames.push_back({400, 0, 40, 70 });
	walk.frames.push_back({440, 0, 40, 70 });
	walk.frames.push_back({480, 0, 40, 70 });
	walk.frames.push_back({520, 0, 40, 70 });
	walk.loop = true;
	walk.speed = 0.15f;

	// Move down
	down.frames.push_back({33, 1, 32, 14});
	down.frames.push_back({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;

	// Particles ---
	// Explosion particle
	explosion.anim.frames.push_back({274, 296, 33, 30});
	explosion.anim.frames.push_back({313, 296, 33, 30});
	explosion.anim.frames.push_back({346, 296, 33, 30});
	explosion.anim.frames.push_back({382, 296, 33, 30});
	explosion.anim.frames.push_back({419, 296, 33, 30});
	explosion.anim.frames.push_back({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	
	// Laser particle
	laser.anim.frames.push_back({200, 120, 32, 12});
	laser.anim.frames.push_back({230, 120, 32, 12});
	laser.speed.x = 7;
	laser.life = 1000;
	laser.anim.speed = 0.05f;


}

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start() {
	LOG("Loading player");

	flip = SDL_FLIP_NONE;
	graphics = App->textures->Load("characters\\scott_p1.png");

	position.x = 150;
	position.y = 120;

	SDL_Texture* particles = App->textures->Load("particles.png");
	explosion.graphics = laser.graphics = particles;

	explosion.fx = App->audio->LoadFx("explosion.wav");
	laser.fx = App->audio->LoadFx("slimeball.wav");

	collider = App->collision->AddCollider({0, 0, 40, 70}, COLLIDER_PLAYER, this);

	finished = false;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp() {
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update() {
	int speed = 1;

	if(finished == true)
		return UPDATE_CONTINUE;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		flip = SDL_FLIP_HORIZONTAL;
		position.x -= speed;
		if (current_animation != &walk) {
			walk.Reset();
			current_animation = &walk;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		flip = SDL_FLIP_NONE;
		position.x += speed;
		if (current_animation != &walk) {
			walk.Reset();
			current_animation = &walk;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		position.y += speed;
		if (current_animation != &walk) {
			walk.Reset();
			current_animation = &walk;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		position.y -= speed;
		if(current_animation != &walk) {
			walk.Reset();
			current_animation = &walk;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP) {
		//App->particles->AddParticle(laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		current_animation = &idle;

	collider->SetPos(position.x, position.y);

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), flip);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if(c1 == collider && finished == false) {
		//App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_NONE);
		//App->fade->FadeToBlack((Module*) App->scene_intro, (Module*) App->scene_level1, 1.0f);
		//finished = true;
	}
}