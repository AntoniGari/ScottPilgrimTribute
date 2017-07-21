#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision() : Module() {
	debug = false;

	// Matrix is game specific, change it to adapt to your own needs
	// ... think of moving this outside ModuleCollision
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
}

// Destructor
ModuleCollision::~ModuleCollision() {}

update_status ModuleCollision::PreUpdate() {
	// Remove all colliders scheduled for deletion
	for(list<Collider*>::iterator it = colliders.begin(); it != colliders.end();) {
		if((*it)->to_delete == true) {
			RELEASE(*it);
			it = colliders.erase(it);
		} else
			++it;
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update() {
	Collider* c1;
	Collider* c2;

	for(list<Collider*>::iterator it = colliders.begin(); it != colliders.end();) {
		c1 = *it;

		for(list<Collider*>::iterator it2 = ++it; it2 != colliders.end(); ++it2) {
			c2 = *it2;

			if(c1->CheckCollision(c2->rect) == true) {
				if(matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if(matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::PostUpdate() {
	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		debug = !debug;

	if(debug == true) {
		for(list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it) {
			Collider* col = *it;
			Uint8 alpha = 100;
			switch(col->type) {
				case COLLIDER_NONE:
				App->renderer->DrawQuad(col->rect, 255, 255, 255, alpha);
				break;
				case COLLIDER_WALL:
				App->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
				break;
				case COLLIDER_PLAYER:
				App->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
				break;
				case COLLIDER_ENEMY:
				App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
				break;
				case COLLIDER_PLAYER_SHOT:
				App->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
				break;
				case COLLIDER_ENEMY_SHOT:
				App->renderer->DrawQuad(col->rect, 0, 255, 255, alpha);
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCollision::CleanUp() {
	LOG("Freeing all colliders");

	for(list<Collider*>::reverse_iterator it = colliders.rbegin(); it != colliders.rend(); ++it)
		RELEASE(*it);

	colliders.clear();
	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback) {
	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret);
	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(SDL_Rect r) const {
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}