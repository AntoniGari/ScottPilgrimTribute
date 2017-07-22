#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel1.h"
#include "ModuleSceneIntro.h"
#include "SDL/include/SDL_render.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled) {}

ModuleSceneIntro::~ModuleSceneIntro() {}

// Load assets
bool ModuleSceneIntro::Start() {
	LOG("Loading Intro assets");
	bool ret = true;

	graphics = App->textures->Load("sprites_ui\\start.png");
	App->audio->PlayMusic("music\\01-scott-pilgrim-anthem.ogg", 0.0f);
	fx = App->audio->LoadFx("starting.wav");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp() {
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update() {
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL, SDL_FLIP_NONE);

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP) {
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(App->scene_level1, this, 1.0f);
	}

	return UPDATE_CONTINUE;
}