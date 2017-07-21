#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/include/SDL_rect.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int32 uint32;

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status {
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x ) { \
       if( x != nullptr ) { \
         delete x; \
	     x = nullptr; \
       } \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) { \
       if( x != nullptr ) { \
           delete[] x; \
	       x = nullptr; \
		 } \
	 }

// Configuration -----------
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 240
#define SCREEN_SIZE 3
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Scott Pilgrim vs. the World"

#endif //__GLOBALS_H__