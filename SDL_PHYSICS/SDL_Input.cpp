#include "SDL_Input.h"

/// 
/// SDL_Input.cpp
/// SDL Assignment 2
/// This class is for handling any input used within an SDL Render Window.
/// Created by Joshua Cook -- 2015
/// 

/// Input Constructor.
/// Initialises all keyboard inputs to false.
SDL_Input::SDL_Input(void)
{
	// initialise all keys to false
	for (int i = 0; i < 323; i++)
	{
		keysHeld[i] = false;
	}
}

SDL_Input::~SDL_Input(void)
{
}

/// Input Update.
/// Updates the keyBuffer array when called.
void SDL_Input::Update()
{
	if (SDL_PollEvent(&incomingEvent))
	{
		// update the array of keys
		if (incomingEvent.type == SDL_KEYDOWN)
		{
			keysHeld[incomingEvent.key.keysym.sym] = true;
		}
		if (incomingEvent.type == SDL_KEYUP)
		{
			keysHeld[incomingEvent.key.keysym.sym] = false;
		}
	}
}

/// Key Pressed.
/// returns the value of a passed in index for the keyBuffer array.
bool SDL_Input::isKeyDown(int key)
{
	if(key > 322)
		return false;

	return keysHeld[key];
}

/// Escape Key.
/// A singled out function to see if the Escape key is pressed.
bool SDL_Input::Esc()
{
	return keysHeld[SDLK_ESCAPE];
}