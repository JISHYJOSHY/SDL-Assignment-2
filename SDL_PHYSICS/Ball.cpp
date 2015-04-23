#include "Ball.h"

/// 
/// Ball.h
/// SDL Assignment 2
/// This class is to control the physics of the ball
/// Created by Joshua Cook -- 2015
/// 

Ball::Ball(void)
{
	acceleration = glm::vec3(0, 0, 0);
}

Ball::~Ball(void)
{
}

float magnitude(glm::vec3 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z + v.z));
}

float distance(glm::vec3 a, glm::vec3 b)
{
	float A = a.x - b.x, B = a.y - b.y, C = a.z - b.z;
	return sqrt((A * A) + (B * B) + (C * C));
}

void Ball::Update(std::vector<Ball*>& balls, float dt)
{
	acceleration.y -= 9.81f * dt;
	position += acceleration * dt;
	acceleration *= 0.99f;


	if(position.x + acceleration.x * dt < 1.9f
	|| position.x + acceleration.x * dt > -1.9f
	|| position.z + acceleration.z * dt < 3.9f
	|| position.z + acceleration.z * dt > -3.9f)
	{
	// Temporary bounding box
		if(position.y + acceleration.y * dt < 0.6f)
		{
			position -= acceleration * dt;
			acceleration.y *= -0.8f;
		}
	}

	unsigned int ballSize = balls.size();
	for(int i = 0; i < ballSize; i++)
	{
		// change this, this is currently the radius of the mesh
		float maxDist = 0.217 * 2;
		float dist = distance(position, balls[i]->position);

		if(dist < maxDist)
		if(!isThis(balls[i]))
		{
			// workout the direction
			glm::vec3 dir = glm::normalize(position - balls[i]->position);

			// calculate the force
			float force = maxDist - dist + 0.01f;

			// move this ball
			position += dir * force;

			// use the magnitude to calculate the acceleration next frame
			float mag1 = magnitude(acceleration), mag2 = magnitude(balls[i]->acceleration);
			acceleration = dir * (mag1 / 2.f + mag2 / 2.f);
			balls[i]->acceleration = dir * (-(mag2 / 2.f + mag1 / 2.f));
		}
	}
}

void Ball::Kick(glm::vec3 force)
{
	acceleration += force;
}

void Ball::Orbit(glm::vec3 pos, float dt)
{
	float gravityForce = 70.f;
	glm::vec3 direction = glm::normalize(position - pos);


	acceleration -= direction * gravityForce * dt;
}

void Ball::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, Light light)
{
	UpdateObject();
	mesh->Draw(viewMatrix, projMatrix, light);
}

bool Ball::isThis(Ball* ball)
{
	if(ball->scale == this->scale)
		if(ball->position == this->position)
			if(ball->rotation == this->rotation)
				return true;
	return false;
}