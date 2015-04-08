#ifndef _MESH_H_
#define _MESH_H_

/// 
/// Mesh.h
/// SDL Assignment 2
/// Class to hold mesh vertex data
/// Created by Joshua Cook -- 2015
/// 

#include <glm.hpp>
#include <SDL.h>
#include "glew.h"

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	/// Loads object model into OpenGL
	void InitialiseVAO();

	/// Loads shaders for the object into OpenGL
	void InitialiseShaders();

	void Update(glm::vec3 pos, glm::vec3 rot);
		
	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);


private:

	/// Vertex Array Object for model in OpenGL
	GLuint VAO;

	/// Shader program
	GLuint program;

	/// Uniform locations
	GLint shaderModelMatLocation, shaderViewMatLocation, shaderProjMatLocation;

	/// Object's model matrix
	/// This is rebuilt in the update function
	glm::mat4 modelMatrix;

	/// Number of vertices in the model
	unsigned int numVertices;

};

#endif