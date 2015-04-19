#ifndef _MATERIAL_H_
#define _MATERIAL_H_

/// 
/// Material.h
/// SDL Assignment 2
/// Class to hold a meterial file information
/// Created by Joshua Cook -- 2015
/// 

#include <glm.hpp>
#include <string>
#include "glew.h"

class Material
{
public:
	Material(std::string matName, float a, float Ns, float Ni, float* dif, float* amb, float* spec, int illum, int tex);
	~Material(void);

private:
	std::string name;
	float alpha, ns, ni;
	float diffuse[3], ambient[3], specular[3];
	int illumination;
	int texture;
};

#endif