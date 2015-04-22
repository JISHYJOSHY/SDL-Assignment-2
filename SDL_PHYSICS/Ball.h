#ifndef _BALL_H_
#define _BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball(void);
	~Ball(void);

	void Update(std::vector<Ball*>& balls, float dt);
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	void Kick(glm::vec3 force);
	void Orbit(glm::vec3 pos, float dt);

private:
	glm::vec3 acceleration;

	bool isThis(Ball* ball);
};

#endif