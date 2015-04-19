#include "Material.h"

/// 
/// Material.cpp
/// SDL Assignment 2
/// Class to hold a meterial file information
/// Created by Joshua Cook -- 2015
/// 

Material::Material(std::string matName, float a, float Ns, float Ni, float* dif, float* amb, float* spec, int illum, int tex)
{
	name = matName;
	alpha = a;
	ns = Ns;
	ni = Ni;

	diffuse[0] = dif[0];
	diffuse[1] = dif[1];
	diffuse[2] = dif[2];
	
	ambient[0] = amb[0];
	ambient[1] = amb[1];
	ambient[2] = amb[2];
	
	specular[0] = spec[0];
	specular[1] = spec[1];
	specular[2] = spec[2];

	illumination = illum;
	texture = tex;
}


Material::~Material(void)
{
}
