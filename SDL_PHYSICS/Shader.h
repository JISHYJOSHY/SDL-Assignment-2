#ifndef _SHADER_H_
#define _SHADER_H_

/// 
/// Shader.h
/// SDL Assignment 2
/// Class to hold mesh shader data
/// Created by Joshua Cook -- 2015
/// 

#include "glew.h"
#include <string>

class Shader
{
public:
	Shader(void);
	~Shader(void);
	
	/// Loads shaders for the object into OpenGL
	void InitialiseShader();
	
	/// Functions to get the GLint information outside of the class
	inline GLuint Program() { return program; };
	inline GLint ModelMat() { return modelMatLocation; };
	inline GLint ViewMat() { return viewMatLocation; };
	inline GLint ProjMat() { return projMatLocation; };

private:	
	/// Shader program
	GLuint program;

	/// Uniform locations
	GLint modelMatLocation, viewMatLocation, projMatLocation;

	std::string ReadFile(std::string filename);

};

#endif