#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/// 
/// Texture.h
/// SDL Assignment 2
/// This class operates to hold texture information
/// Created by Joshua Cook -- 2015
/// 

#include <string>
#include <SDL.h>
#include "glew.h"

class Texture
{
public:
	Texture(std::string filename);
	~Texture(void);

	inline unsigned int getTexID() { return texID; };

private:
	void LoadTexture(std::string filename);

	unsigned int texID;
};

#endif