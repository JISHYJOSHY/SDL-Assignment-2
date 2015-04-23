#include "Texture.h"
#include <iostream>

/// 
/// Texture.h
/// SDL Assignment 2
/// This class operates to hold texture information
/// Created by Joshua Cook -- 2015
/// 

Texture::Texture(std::string filename)
{
	LoadTexture(filename);
}


Texture::~Texture(void)
{
}

void Texture::LoadTexture(std::string filename)
{
	// load bmp through SDL
	SDL_Surface* image = SDL_LoadBMP(filename.c_str());
	
	// check if it has loaded
	if (!image)
	{
		std::cout << "FAILED : Cannot open file:"  << std::endl;
		return;
	}

	std::cout << "SUCCESS : Texture loaded" << std::endl;
	
	// use the SDL imported data to generate a texture through glew
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// BMP files are loaded in with the colour channels backwards, so we need to process it as a BGR instead of RGB
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	// OpenGL now has our image data, so we can free the loaded image
	SDL_FreeSurface(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
}