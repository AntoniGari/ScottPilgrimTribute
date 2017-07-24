#include <math.h>
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

using namespace std;

ModuleParticles::ModuleParticles() : Module() {}

ModuleParticles::~ModuleParticles() {}

// Update: draw background
update_status ModuleParticles::PostUpdate() {
	for(list<Particle*>::iterator it = active.begin(); it != active.end();) {
		Particle* p = *it;

		if(p->Update() == false) {
			RELEASE(p);
			it = active.erase(it);
			break;
		} else if(p->timer.Read() > p->delay) {
			App->renderer->Blit(p->graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->flip);
			if(p->fx_played == false) {
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}
		++it;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	for(list<Particle*>::iterator it = active.begin(); it != active.end(); ++it) {
		if((*it)->collider == c1) {
			RELEASE(*it);
			it = active.erase(it);
			break;
		}
	}
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, SDL_RendererFlip flip, Uint32 delay) {
	Particle* p = new Particle(particle);
	p->timer.Start();
	p->position.x = x;
	p->position.y = y;
	p->flip = flip;
	p->delay = delay;

	if(collider_type != COLLIDER_NONE) {
		p->collider = App->collision->AddCollider({p->position.x, p->position.y, 0, 0}, collider_type, this);
	}

	active.push_back(p);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::~Particle() {
	if(collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update() {
	bool ret = true;

	if(life > 0) {
		if(timer.Read() > delay + life)
			ret = false;
	} else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != NULL) {
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x, position.y, r.w, r.h};
	}

	return ret;
}