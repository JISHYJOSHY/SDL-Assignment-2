#include "Shader.h"

/// 
/// Shader.h
/// SDL Assignment 2
/// Class to hold mesh shader data
/// Created by Joshua Cook -- 2015
/// 

#include <iostream>
#include <gtc/matrix_transform.hpp>

// This does not belong here - should really have a nice shader class etc for sorting all this stuff out!
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
	shaderModelMatLocation = shaderViewMatLocation = shaderProjMatLocation = 0;

	// Create the shaders
	InitialiseShader();
}


Shader::~Shader(void)
{
}

/// Create the shader
void Shader::InitialiseShader()
{
	// OpenGL doesn't provide any functions for loading shaders from file
	// I'm feeling lazy, so just hardcoding them here

	// This is the vertex shader
	const GLchar *vShaderText = "#version 430 core\n\
						 layout(location = 0) in vec4 vPosition;\n\
						 layout(location = 1) in vec3 vNormalIn;\n\
						 \n\
						 uniform mat4 modelMat;\n\
						 uniform mat4 invModelMat;\n\
						 uniform mat4 viewMat;\n\
						 uniform mat4 projMat;\n\
						 \n\
						 uniform vec4 worldSpaceLightPos = {1,0.8,1,1};\n\
						 \n\
						 out vec3 vNormalV;\n\
						 out vec3 lightDirV;\n\
						 \n\
						 void main()\n\
						 {\n\
								gl_Position = projMat * viewMat * modelMat * vPosition;\n\
								\n\
								vec4 eyeSpaceVertPos = viewMat * modelMat * vPosition;\n\
								vec4 eyeSpaceLightPos = viewMat * worldSpaceLightPos;\n\
								\n\
								lightDirV =  normalize( vec3(eyeSpaceLightPos) - vec3(eyeSpaceVertPos) );\n\
								\n\
								vNormalV = mat3(viewMat * modelMat) * vNormalIn;\n\
						 }";

	// This is the fragment shader
	const GLchar *fShaderText = "#version 430 core\n\
								in vec3 lightDirV;\n\
								in vec3 vNormalV;\n\
								\n\
								uniform vec3 lightColour = {1,1,1};\n\
								uniform vec3 emissiveColour = {0,0,0};\n\
								uniform vec3 ambientColour  = {0.1f,0.1f,0.2f};\n\
								uniform vec3 diffuseColour  = {0.8f,0.1f,0.1f};\n\
								uniform vec3 specularColour = {0.0f,0.0f,0.0f};\n\
								uniform float shininess     = 50.0f;\n\
								uniform float alpha         = 1.0f;\n\
								\n\
								out vec4 fragColour;\n\
								\n\
								void main()\n\
								{\n\
									vec3 lightDir = normalize( lightDirV );\n\
									vec3 vNormal = normalize( vNormalV );\n\
									\n\
										vec3 diffuse = diffuseColour * lightColour * max( dot( vNormal, lightDir ), 0);\n\
										\n\
										fragColour = vec4( emissiveColour + ambientColour + diffuse, alpha);\n\
								}";
						 // 
						 /*
									vec3 ambient = vec3();
									vec3 diffuse = vec3(1.0f,0.3f,0.3f) * max(dot( normalize(lightDir), normalize(vNormal) ),0);
									fColor = vec4( ambient + diffuse, 1.0f);
									*/

	// The 'program' stores the shaders
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
	shaderModelMatLocation = glGetUniformLocation( program, "modelMat" );
	shaderViewMatLocation = glGetUniformLocation( program, "viewMat" );
	shaderProjMatLocation = glGetUniformLocation( program, "projMat" );
}