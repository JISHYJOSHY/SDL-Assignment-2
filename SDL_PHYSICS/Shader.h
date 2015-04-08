#ifndef _SHADER_H_
#define _SHADER_H_

/// 
/// Shader.h
/// SDL Assignment 2
/// Class to hold mesh shader data
/// Created by Joshua Cook -- 2015
/// 

#include <glm.hpp>
#include <SDL.h>
#include "glew.h"

class Shader
{
public:
	Shader(void);
	~Shader(void);
	
	/// Loads shaders for the object into OpenGL
	void InitialiseShader();
	
	/// Functions to get the GLint information outside of the class
	inline GLuint Program() { return program; };
	inline GLint ModelMat() { return shaderModelMatLocation; };
	inline GLint ViewMat() { return shaderViewMatLocation; };
	inline GLint ProjMat() { return shaderProjMatLocation; };

private:	

	/// Shader program
	GLuint program;

	/// Uniform locations
	GLint shaderModelMatLocation, shaderViewMatLocation, shaderProjMatLocation;

};

#endif