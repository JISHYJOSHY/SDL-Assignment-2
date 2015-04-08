#ifndef _APPLICATION_H_
#define _APPLICATION_H_

/// 
/// Application.h
/// SDL Assignment 2
/// This class contains variables and data to handle the update and drawing of an OpenGL executable.
/// Created by Joshua Cook -- 2015
/// 

#include <SDL.h>
#include <iostream>
#include "glew.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "SDL_Input.h"
#include "GameObject.h"

class Application
{
public:
	Application(int WIDTH, int HEIGHT);
	~Application(void);

	bool init();
	void run();

	void initObjects();

private:
	bool running;

	void Update(float dt);
	void Draw();

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_GLContext glcontext;
	SDL_Input* input;
	GameObject* test;
	Mesh* mesh;

	int winWidth;
	int winHeight;
};

#endif