#include "Application.h"

/// 
/// Application.cpp
/// SDL Assignment 2
/// This class contains variables and data to handle the update and drawing of an OpenGL executable.
/// Created by Joshua Cook -- 2015
/// 

Application::Application(int WIDTH, int HEIGHT)
{
	winWidth = WIDTH;
	winHeight = HEIGHT;
}

Application::~Application(void)
{
}

/// Initialisation of Application.
/// Includes the startup of SDL and OpenGL.
bool Application::init()
{
	// first init SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "Could not initialise SDL" << std::endl;
		return false;
	}

	// then tell SDL we are using OpenGL	
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// create a window
	window = SDL_CreateWindow("Joshua Cook SDL", 100, 100, winWidth, winHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// create the buffer
	renderer = SDL_CreateRenderer(window, -1, 0);

	// create OpenGL Context thing...
	glcontext = SDL_GL_CreateContext(window);

	// then load GLEW
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "Error: GLEW failed to initialise with message: " << glewGetErrorString(err) <<std::endl;
		return false;
	}

	// spit out GLEW + OpenGL info
	std::cout<<"INFO: Using GLEW "<< glewGetString(GLEW_VERSION)<<std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString( GL_VENDOR ) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString( GL_RENDERER ) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

	glEnable(GL_DEPTH_TEST);
	running = true;

	initObjects();

	return true;
}

/// Initialisation of Objects.
/// Spserates the creation of the window and creation of GameObjects.
void Application::initObjects()
{
	input = new SDL_Input();
	test = new GameObject();
	test->SetPosition(0,0,0);
}

/// Frame Step of Application.
/// Includes 'most' of the computation for the applications entities.
void Application::Update(float dt)
{
	input->Update();
	
	test->Update(dt);
}

/// Draw Step of Application.
/// Includes the drawing of entities in the application.
void Application::Draw()
{	
	// Draw our world

	// Specify the colour to clear the framebuffer to
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	// This writes the above colour to the colour part of the framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Construct a projection matrix for the camera
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Create a viewing matrix for the camera
	// Don't forget, this is the opposite of where the camera actually is
	// You can think of this as moving the world away from the camera
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-2.5f) );

	// Draw the object using the given view (which contains the camera orientation) and projection (which contains information about the camera 'lense')
	test->Draw( View, Projection);

	// This tells the renderer to actually show its contents to the screen
	// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
	SDL_GL_SwapWindow( window );
}

/// Game Loop.
/// Not much to say here, constantly goes over Update and Draw functions
void Application::run()
{	
	unsigned int lastTime = SDL_GetTicks();

	while(running)
	{
		unsigned int current = SDL_GetTicks();
		float dt = (float) (current - lastTime) / 1000.0f;
		lastTime = current;

		Update(dt);
		Draw();

		if(input->Esc())
			running = false;
		
		if( dt < (1.0f/50.0f) )
		{
			SDL_Delay((unsigned int) (((1.0f/50.0f) - dt) * 1000.0f));
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}