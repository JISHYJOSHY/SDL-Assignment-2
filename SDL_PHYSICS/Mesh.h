#ifndef _MESH_H_
#define _MESH_H_

/// 
/// Mesh.h
/// SDL Assignment 2
/// Class to hold mesh vertex data
/// Created by Joshua Cook -- 2015
/// 

#include <glm.hpp>
#include <SDL.h>
#include <string>
#include <vector>
#include "glew.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh(std::string filename);
	~Mesh(void);

	/// Loads object model into OpenGL
	void LoadMesh(std::string filename);
	
	void Update(glm::vec3 pos, glm::vec3 rot);
		
	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, Shader *shader);

private:

	/// Vertex Array Object for model in OpenGL
	GLuint VAO;

	/// Object's model matrix
	/// This is rebuilt in the update function
	glm::mat4 modelMatrix;

	/// Number of vertices in the model
	unsigned int numVertices;
	
	struct Face
	{
		int vertex;
		int texture;
		int normal;
		bool quad;

		Face(int vert, int text, int norm, bool quad) : vertex(vert), texture(text), normal(norm), quad(quad) {};
	};

	/*
	struct Material
	{
		std::string name;
		float alpha, ns, ni;
		float dif[3], amb[3], spec[3];

		int illum;
		int texture;
		Material();
	};

	struct TextureCoord
	{
		float u, v;
		TextureCoord(float a, float b) : u(a), v(b) {};
	};
	*/
	std::vector<glm::vec3> verticesVector;
	std::vector<glm::vec3> normalsVector;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

	std::vector<Face> faces;

};

#endif