/***************************************************************
	This source code taken from Lazy Foo' SDL tutorial lesson 17 
	http://lazyfoo.net/SDL_tutorials/lesson17/index.php
***************************************************************/

#include "SDL/SDL.h"

#ifndef TIMER_H
#define TIMER

class Timer
{
private:
	//The ticks when the timer started
	int startTicks;
	//The ticks stored when the timer paused
	int pausedTicks;

	//The timer status
	bool started;
	bool paused;

public:
	//Constructor - Initialize variables
	Timer();

	//Timer actions
	void start();
	void stop();
	void pause();
	void unpause();
	
	//Gets the timer time
	int get_ticks();

	//Check the status of the timer
	bool is_started();
	bool is_paused();
};

#endif
