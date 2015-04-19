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
#include "Material.h"

class Mesh
{
public:
	Mesh(std::string filename);
	~Mesh(void);
	
	/// Update the object based on an input pos and rotation
	void Update(glm::vec3 pos, glm::vec3 rot);
		
	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, Shader *shader);

private:	
	/// Loads object model into OpenGL
	void LoadMesh(std::string filename);
	/// Loads a texture into a GLuint
	unsigned int LoadImage(std::string filename);

	/// Create VAO
	void CreateVAO();

	/// Vertex Array Object for model in OpenGL
	GLuint VAO;

	/// GLuint for texture data
	std::vector<unsigned int> textures;

	/// Materials
	std::vector<Material> materials;

	/// Don't Know
	bool mat, tex, norm;

	/// Buffers	
	GLuint positionBuffer;
	GLuint normalBuffer;
	GLuint uvBuffer;

	/// Object's model matrix
	/// This is rebuilt in the update function
	glm::mat4 modelMatrix;

	/// Number of vertices in the model
	unsigned int numVertices;
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
};

#endif