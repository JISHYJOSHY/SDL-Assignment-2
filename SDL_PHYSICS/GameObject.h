#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

/// 
/// GameObject.h
/// SDL Assignment 2
/// General GameObject class to be inherited from
/// Created by Joshua Cook -- 2015
/// 

#include <glm.hpp>
#include <SDL.h>
#include "glew.h"

class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	/// Loads object model into OpenGL
	void InitialiseVAO();

	/// Loads shaders for the object into OpenGL
	void InitialiseShaders();

	/// Currently just updates rotation to make the model rotate
	void Update( float deltaTs );

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	/// For setting the position of the model
	void SetPosition( float posX, float posY, float posZ ) {position.x = posX; position.y = posY; position.z = posZ;}

protected:

	/// Object position vector
	glm::vec3 position;

	/// Euler angles for rotation
	glm::vec3 rotation;

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