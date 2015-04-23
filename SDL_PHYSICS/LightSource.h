#ifndef _LIGHT_H
#define _LIGHT_H

/// 
/// Light.h
/// SDL Assignment 2
/// This class contains information on lights
/// Created by Joshua Cook -- 2015
/// 

#include <glm.hpp>

class Light
{
public:
	Light(void);
	~Light(void);

	inline glm::vec3 getPos() { return pos; };
	inline void setPos(glm::vec3 p) { pos = p; };

private:
	glm::vec3 pos;
};

#endif