#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"

class Timer {
public:

	// Constructor
	Timer();

	void Start();
	void Stop();
	void Reset();

	uint32 Read();

	bool Compare(Uint32);
	bool isRunning();

private:

	bool	running;
	uint32	started_at;
	uint32	stopped_at;
};

#endif //__TIMER_H__