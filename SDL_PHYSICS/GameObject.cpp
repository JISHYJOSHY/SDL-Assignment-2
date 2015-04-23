#include "GameObject.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

/// 
/// GameObject.cpp
/// SDL Assignment 2
/// General GameObject class to be inherited from
/// Created by Joshua Cook -- 2015
/// 

GameObject::GameObject()
{
	mesh = NULL;
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
}

GameObject::~GameObject()
{
	delete mesh;
}

void GameObject::Update(float dt)
{
}

void GameObject::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, Light light)
{
	// check to see if this gameobject has a mesh attached
	if(mesh != NULL)
	{
		// and draw the mesh
		mesh->Draw(viewMatrix, projMatrix, light);
	}
}

void GameObject::AttachMesh(Mesh &meshObject)
{
	// set the local pointer to a loaded mesh
	mesh = &meshObject;
}

void GameObject::UpdateObject()
{
	// update the mesh attached

	// if the gameobject has a mesh
	if(mesh != NULL)
	{
		// update the meshes matrix
		mesh->Update(position, rotation, scale);
	}
}