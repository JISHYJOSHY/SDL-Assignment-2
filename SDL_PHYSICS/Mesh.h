#ifndef _MESH_H_
#define _MESH_H_

/// 
/// Mesh.h
/// SDL Assignment 2
/// This class contains data to handle mesh data from a loaded obj file
/// 

#include <glm.hpp>
#include <SDL.h>
#include <string>
#include "glew.h"
#include "ObjLoader.h"
#include "BoundingBox.h"
#include "LightSource.h"
#include "Texture.h"

/// Class to store and display a model
class Mesh
{
public:

	/// Constructor calls InitialiseVAO and InitialiseShaders
	Mesh(std::string objFileName);
	~Mesh();
	
	/// Load in a texture
	void LoadTexture(const char* filename);

	/// Loads object model into OpenGL
	void InitialiseVAO();

	/// Loads shaders for the object into OpenGL
	void InitialiseShaders();

	/// Currently just updates rotation to make the model rotate
	void Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4& viewMatrix, glm::mat4& projMatrix, Light& light);
	
	/// Draws object using the given camera view and projection matrices with a loaded texture
	void Draw(glm::mat4& viewMatrix, glm::mat4& projMatrix, Light& light, Texture* texture);

	inline BoundingBox* getBB() { return bb; };
	
protected:
	// process an obj file
	ObjLoader objLoader;

	/// Vertex Array Object for model in OpenGL
	GLuint VAO;

	/// Shader program
	GLuint shader;

	/// Object's model matrix
	/// This is rebuilt in the update function
	glm::mat4 modelMatrix;
	
	// opengl index for the loaded textures
	GLuint diffuseTexID;
	GLuint normalTexID;
	// Get a handle for our "MVP" uniform
	GLuint matrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

private:
	// private buffers for the loaded model data
	GLuint positionBuffer;
	GLuint normalBuffer;
	GLuint texCoordBuffer;
	GLuint tangentBuffer;
	GLuint biTangentBuffer;

	std::string ReadFile(std::string fileName);

	BoundingBox* bb;
	unsigned int numVertices;
};


#endif
