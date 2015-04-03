#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SDL.h>
#include <iostream>
#include "glew.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Application
{
public:
	Application(int WIDTH, int HEIGHT);
	~Application(void);

	bool init();
	void run();

private:
	bool running;

	void Update();
	void Draw();

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_GLContext glcontext;

	int winWidth;
	int winHeight;
};

#endif