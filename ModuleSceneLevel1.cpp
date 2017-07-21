#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleSceneLevel1.h"

ModuleSceneLevel1::ModuleSceneLevel1(bool start_enabled) : Module(start_enabled) {
	background = NULL;
	stars = NULL;
}

ModuleSceneLevel1::~ModuleSceneLevel1() {}

// Load assets
bool ModuleSceneLevel1::Start() {
	LOG("Loading space scene");
	
	background = App->textures->Load("backgrounds\\level1.png");

	App->collision->Enable(); // enable before player
	App->player->Enable();
	App->audio->PlayMusic("music\\02-another-winter.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//Left Collider
	App->collision->AddCollider({0, 0, 2, 500}, COLLIDER_WALL);

	//App->collision->AddCollider({1376, 0, 112, 95}, COLLIDER_WALL);
	//App->collision->AddCollider({1376, 144, 112, 95}, COLLIDER_WALL);

	return true;
}

// UnLoad assets
bool ModuleSceneLevel1::CleanUp() {
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneLevel1::Update() {
	// Move camera forward -----------------------------
	int scroll_speed = 1;

	//App->player->position.x += 1;
	//App->renderer->camera.x -= 3;
	
	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}