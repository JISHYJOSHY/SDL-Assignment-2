#ifndef _INPUT_H_
#define _INPUT_H_

/// 
/// SDL_Input.h
/// SDL Assignment 2
/// This class is for handling any input used within an SDL Render Window.
/// Created by Joshua Cook -- 2015
/// 

#include <SDL.h>

class SDL_Input
{
public:
	SDL_Input(void);
	~SDL_Input(void);

	// update key status
	void Update();

	bool isKeyDown(int key);

	bool Esc();

private:
	SDL_Event incomingEvent;
	bool keysHeld[323];
};

#endif