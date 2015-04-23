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
#include "Mesh.h"

class GameObject
{
public:
	GameObject(void);
	~GameObject(void);
	/// Currently just updates rotation to make the model rotate
	void Update(float dt);

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, Light light);
	
	/// For setting the position of the model
	void SetPosition( float posX, float posY, float posZ ) { position.x = posX; position.y = posY; position.z = posZ; }

	inline glm::vec3 getPosition() { return position; };
	inline glm::vec3 getRotation() { return rotation; };
	inline glm::vec3 getScale() { return scale; };

	/// For attaching a mesh to the local Mesh pointer
	void AttachMesh(Mesh &meshObject);
	void UseTexture(Texture &textureFile);

	inline Mesh getMesh() { return *mesh; };
	inline GLuint getTexID() { return texID; };

protected:
	/// Object position vector
	glm::vec3 position;

	/// Euler angles for rotation
	glm::vec3 rotation;

	/// Object scale vector
	glm::vec3 scale;

	/// Pointers to existing meshes and textures
	Mesh* mesh;
	Texture* texture;

	void UpdateObject();
};

#endif