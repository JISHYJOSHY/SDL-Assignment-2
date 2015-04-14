#include "Camera.h"

/// 
/// Camera.cpp
/// SDL Assignment 2
/// Class to control view matrices for objects and stuff
/// Created by Joshua Cook -- 2015
/// 

Camera::Camera(void)
{
	speed = 3.0f;
	mouseSpeed = 0.005f;

	pitch = 0;
	yaw = 0;
	
	fov = 70;
	position = glm::vec3(0, 0, 3);
}

Camera::~Camera(void)
{
}

void Camera::Update(SDL_Input* input, float dt)
{	
	unsigned int x = input->mousePosition().x;
	unsigned int y = input->mousePosition().y;
	// Compute orientinput->mousePosition().y;ation
	pitch += mouseSpeed * input->mousePosition().x;
	yaw += mouseSpeed * input->mousePosition().y;
	
	// Direction
	glm::vec3 direction(cos(yaw) * sin(pitch), sin(yaw), cos(yaw) * cos(pitch));
	
	// Right vector
	glm::vec3 right = glm::vec3(sin(pitch - 3.14f/2.0f), 0, cos(pitch - 3.14f/2.0f));
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	projectionMatrix = glm::perspective(fov, 16.0f / 9.0f, 0.1f, 100.0f);

	viewMatrix  = glm::lookAt(position,	position+direction,	up);
}