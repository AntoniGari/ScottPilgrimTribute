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
	//Idle Animation
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

	//Walk Animation
	walk.frames.push_back({320, 0, 40, 70 });
	walk.frames.push_back({360, 0, 40, 70 });
	walk.frames.push_back({400, 0, 40, 70 });
	walk.frames.push_back({440, 0, 40, 70 });
	walk.frames.push_back({480, 0, 40, 70 });
	walk.frames.push_back({520, 0, 40, 70 });
	walk.loop = true;
	walk.speed = 0.15f;

	//Run Animation
	run.frames.push_back({560, 0, 60, 70 });
	run.frames.push_back({620, 0, 60, 70 });
	run.frames.push_back({680, 0, 60, 70 });
	run.frames.push_back({740, 0, 60, 70 });
	run.frames.push_back({800, 0, 60, 70 });
	run.frames.push_back({860, 0, 60, 70 });
	run.frames.push_back({920, 0, 60, 70 });
	run.frames.push_back({980, 0, 60, 70 });
	run.loop = true;
	run.speed = 0.15f;

	// Particles ---
	// Dust particle
	
	dust.anim.frames.push_back({0, 0, 40, 30});
	dust.anim.frames.push_back({40, 0, 40, 30 });
	dust.anim.frames.push_back({80, 0, 40, 30 });
	dust.anim.frames.push_back({120, 0, 40, 30 });
	dust.anim.frames.push_back({160, 0, 40, 30 });
	dust.anim.loop = false;
	dust.anim.speed = 0.15f;
	
	// Laser particle
	/*
	laser.anim.frames.push_back({200, 120, 32, 12});
	laser.anim.frames.push_back({230, 120, 32, 12});
	laser.speed.x = 7;
	laser.life = 1000;
	laser.anim.speed = 0.05f;
	*/

}

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start() {
	LOG("Loading player");

	flip = SDL_FLIP_NONE;
	graphics = App->textures->Load("sprites_characters\\scott_p1.png");

	position.x = 150;
	position.y = 120;

	SDL_Texture* particles = App->textures->Load("sprites_characters\\particles.png");
	//dust.graphics = coin.graphics = particles;
	dust.graphics = particles;


	//explosion.fx = App->audio->LoadFx("explosion.wav");
	//laser.fx = App->audio->LoadFx("slimeball.wav");

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
	
	if(finished == true)
		return UPDATE_CONTINUE;

	CheckInput();
	
	collider->SetPos(position.x, position.y);

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), flip);

	return UPDATE_CONTINUE;
}

void ModulePlayer::CheckInput() {
	int walkSpeed = 1;
	int runSpeed = 2;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		position.y += walkSpeed;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) != KEY_REPEAT) {
			if (current_animation != &walk) {
				walk.Reset();
				current_animation = &walk;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		position.y -= walkSpeed;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) != KEY_REPEAT) {
			if (current_animation != &walk) {
				walk.Reset();
				current_animation = &walk;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		flip = SDL_FLIP_HORIZONTAL;

		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN)
			App->particles->AddParticle(dust, position.x + 15, position.y + 40, COLLIDER_NONE, flip);

		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
			position.x -= runSpeed;
			if (current_animation != &run) {
				run.Reset();
				current_animation = &run;
			}
		}
		else {
			position.x -= walkSpeed;
			if (current_animation != &walk) {
				walk.Reset();
				current_animation = &walk;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		flip = SDL_FLIP_NONE;

		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN)
			App->particles->AddParticle(dust, position.x - 15, position.y + 40, COLLIDER_NONE, flip);

		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
			position.x += runSpeed;
			if (current_animation != &run) {
				run.Reset();
				current_animation = &run;
			}
		}
		else {
			position.x += walkSpeed;
			if (current_animation != &walk) {
				walk.Reset();
				current_animation = &walk;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		current_animation = &idle;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if(c1 == collider && finished == false) {
		//App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_NONE);
		//App->fade->FadeToBlack((Module*) App->scene_intro, (Module*) App->scene_level1, 1.0f);
		//finished = true;
	}
}