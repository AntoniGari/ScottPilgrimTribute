#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>

using namespace std;

class Animation {
public:
	float speed = 1.0f;
	bool loop = true;
	vector<SDL_Rect> frames;

private:
	float current_frame = 0.0f;
	int loops = 0;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f) {}

	SDL_Rect& GetCurrentFrame() {
		current_frame += speed;
		if(current_frame >= frames.size()) {
			current_frame = (loop) ? 0.0f : frames.size() - 1;
			loops++;
		}
		return frames[(int)current_frame];
	}

	const SDL_Rect& PeekCurrentFrame() const {
		return frames[(int)current_frame];
	}

	bool Finished() {
		return loops > 0;
	}

	void Flip() {
	
	}

	void Reset() {
		current_frame = 0;
	}
};

#endif // __ANIMATION_H__