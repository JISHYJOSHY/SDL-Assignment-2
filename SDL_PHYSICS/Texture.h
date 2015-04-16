#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/// 
/// Texture.h
/// SDL Assignment 2
/// Class to load a texture into OpenGL
/// Created by Joshua Cook -- 2015
/// 

#include <string>
#include <SDL.h>

class Texture
{
public:
	Texture(std::string filename);
	~Texture(void);

	unsigned int Get() { return textureID; };

private:
	void LoadImage(std::string filename);

	unsigned int textureID;
};

#endif