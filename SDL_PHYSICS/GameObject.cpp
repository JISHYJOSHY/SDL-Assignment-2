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
	shader = new Shader();
}

GameObject::~GameObject()
{
	// TODO: destroy VAO, shaders etc
}

void GameObject::Update(float dt)
{
	// update the rotation angle of our cube
	rotation.y += dt * 0.5f;
	while(rotation.y > (3.14159265358979323846 * 2.0))
	{
		rotation.y -= (3.14159265358979323846 * 2.0);
	}

	if(mesh != NULL)
	{
		mesh->Update(position, rotation);
	}
}

void GameObject::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	if(mesh != NULL)
	{
		mesh->Draw(viewMatrix, projMatrix, shader);
	}
}

void GameObject::AttachMesh(Mesh &meshObject)
{
	mesh = &meshObject;
}