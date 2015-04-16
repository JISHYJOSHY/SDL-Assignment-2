#include "Texture.h"

/// 
/// Texture.cpp
/// SDL Assignment 2
/// Class to load a texture into OpenGL
/// Created by Joshua Cook -- 2015
/// 

#include "glew.h"
#include <iostream>

Texture::Texture(std::string filename)
{
	LoadImage(filename);
}

Texture::~Texture(void)
{
}

void Texture::LoadImage(std::string filename)
{
	// START TEXTURE LOADER
	std::cout << "Loading file: '" << filename << "'. ";

	// load bmp through SDL
	SDL_Surface* image = SDL_LoadBMP(filename.data());
	
	// check if it has loaded
	if (!image)
	{
		std::cout << "FAILED : Cannot open file: '" << filename << "'" << std::endl;
		return;
	}

	std::cout << "SUCCESS : Texture loaded" << std::endl;

	// use the SDL imported data to generate a texture through glew
	glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, image->pixels);

			// OpenGL now has our image data, so we can free the loaded image
			SDL_FreeSurface(image);

			// different types of texture filtering

			// basic
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

			// trillinear
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
			glGenerateMipmap(GL_TEXTURE_2D);
}