#include "Shader.h"

/// 
/// Shader.h
/// SDL Assignment 2
/// Class to hold mesh shader data
/// Created by Joshua Cook -- 2015
/// 

#include <iostream>
#include <fstream>
#include <gtc/matrix_transform.hpp>

// Useful little function to just check for compiler errors
bool CheckShaderCompiled( GLint shader )
{
	GLint compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled )
	{
		GLsizei len;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete [] log;

		return false;
	}
	return true;
}

Shader::Shader(void)
{
	program = 0;
	modelMatLocation = viewMatLocation = projMatLocation = 0;

	// Create the shaders
	InitialiseShader();
}

Shader::~Shader(void)
{
}

/// Function to load in a shader
std::string Shader::ReadFile(std::string filename)
{	
	std::string result;

	std::ifstream file(filename);

	if (file.is_open())
	{
		std::string Line = "";
		while (getline(file, Line))
			result += "\n" + Line;
		file.close();
	}
	else
	{
		std::cout << "Could not open file : " << filename << std::endl;
	}

	return result;
}
/// Create the shader
void Shader::InitialiseShader()
{
	// This is the vertex shader
	std::string vShaderText = ReadFile("basicVert.vert");

	// This is the fragment shader
	std::string fShaderText = ReadFile("basicFrag.frag");

	// program to store the shaders
	program = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader( GL_VERTEX_SHADER );
	// Give GL the source for it
	glShaderSource( vShader, 1, &vShaderText, NULL );
	// Compile the shader
	glCompileShader( vShader );
	// Check it compiled and give useful output if it didn't work!
	if( !CheckShaderCompiled( vShader ) )
	{
		return;
	}
	// This links the shader to the program
	glAttachShader( program, vShader );

	// Same for the fragment shader
	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fShader, 1, &fShaderText, NULL );
	glCompileShader( fShader );
	if( !CheckShaderCompiled( fShader ) )
	{
		return ;
	}
	glAttachShader( program, fShader );

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( program );
	// Check this worked
	GLint linked;
	glGetProgramiv( program, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( program, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;

		return;
	}

	// We need to get the location of the uniforms in the shaders
	// This is so that we can send the values to them from the application
	// We do this in the following way: 
	modelMatLocation = glGetUniformLocation( program, "modelMat" );
	viewMatLocation = glGetUniformLocation( program, "viewMat" );
	projMatLocation = glGetUniformLocation( program, "projMat" );
}