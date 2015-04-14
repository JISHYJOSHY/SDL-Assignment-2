#include "Mesh.h"

#include <iostream>
#include <fstream>

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
/// 
/// Mesh.cpp
/// SDL Assignment 2
/// Class to hold mesh vertex data
/// Created by Joshua Cook -- 2015
/// 


Mesh::Mesh(std::string filename)
{
	// Initialise variables
	VAO = 0;
	numVertices = 0;

	// Create the model
	LoadMesh(filename);
	CreateVAO();
}

Mesh::~Mesh(void)
{
}

void Mesh::LoadMesh(std::string filename)
{	
	// START OBJECT LOADER
	std::cout << "Loading file: '" << filename << "'" << std::endl;

	std::ifstream file(filename);
	
	// Check if the file is loaded
	if(file == NULL)
	{
		std::cout << "Cannot open file: '" << filename << "'" << std::endl;
		getchar();
		return;
	}

	// vectors to hold the index of the verts, uv and normals
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	// some temporary vectors to hold the data before we commit it
	std::vector<glm::vec3> tempVertices; 
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;

	// while the file is open, loop through the contents
	while(!file.eof())
	{
		// read the file line by line
		char line[256];
		file.getline(line, 256);

		// if the line begins with a 'v', it is data we can use (vertex, normal or uv)
		if(line[0] == 'v')
		{
			float a, b, c;

			// if the next char is 'n', we have a Vertex Normal
			if(line[1] == 'n')
			{
				sscanf(line, "vn %f %f %f", &a, &b, &c);
				tempNormals.push_back(glm::vec3(a, b, c));	
			}
			// if the next char is 't', we have a Vertex Texture
			else if(line[1] == 't')
			{
				sscanf(line, "vt %f %f", &a, &b);
				tempUVs.push_back(glm::vec2(a, b));
			}
			// else we just have the vertex position
			else
			{				
				sscanf(line, "v %f %f %f", &a, &b, &c);
				tempVertices.push_back(glm::vec3(a, b, c));
			}
		}
		// else if the line begins with 'f', it is a face
		else if(line[0] == 'f')
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			
			// obj have 3 ways to define a face: Vertex/UV/Normal, Vertex//Normal, and Vertex
			// we need to test for each one

			// first we test Vertex/UV/Normal
			int input = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			// if the scan failed (because of unexpected character
			if (input < 9)
			{				
				// we try the next format: Vertex//Normal
				input = sscanf(line, "f %d//%d %d//%d %d//%d", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);

				// in this case there are no UV coords, so we set them to 0
				uvIndex[0] = 0;
				uvIndex[1] = 0;
				uvIndex[2] = 0;
				
				// if the scan failed (because of unexpected character
				if (input < 6)
				{
					// in this case, there are no normals present, so we refuse to load the mesh

					std::cout << "Face cannot be read because there are no normals specified, cancelled loading" << std::endl;
					return;
				}
			}

			// add the current vertex index to the vector
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			
			// add the current yv index to the vector
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			
			// add the current normal index to the vector
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
		
	// allocate a piece of memory before for loop to stop multiple calls of the .size() function
	unsigned int arraySize = vertexIndices.size();
	for(unsigned int i = 0; i < arraySize; i++)
	{
		// Now we assign the verts to the actual vector in the order in which the faces tell us
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index

		// firstly, make sure we aren't missing the vector
		if(vertexIndex > 0)
		{
			// if the index is greater than 0, because OBJ starts at 1 (c++ starts at 0), we can safely remove 1 to translate the index
			glm::vec3 vertex = tempVertices[vertexIndex - 1];

			// and then add the vertex to the vector
			vertices.push_back(vertex);
		}

		// and do the same for the uvs and normals

		if(uvIndex > 0)
		{
			glm::vec2 uv = tempUVs[uvIndex - 1];
			uvs.push_back(uv);
		}

		if(normalIndex > 0)
		{
			glm::vec3 normal = tempNormals[normalIndex - 1];
			normals.push_back(normal);	
		}
	}

	// variable to tell OpenGL how many vertices to draw
	numVertices = vertices.size();

	// END OBJECT LOADER
}

/// Create the VAO after we have loaded the mesh
void Mesh::CreateVAO()
{	
	// Create VAO and start binding process
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	// Variable for storing a VBO
	GLuint positionBuffer = 0;

	// Create a buffer and send the vertex information to it
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(0);
	
	// Variable for storing a VBO
	GLuint normalBuffer = 0;

	// Create a buffer and send the normal information to it
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(1);	

	// Reset OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray( 0 );

	glDisableVertexAttribArray(0);
}

/// Update the mesh position and rotation based on an objects pos + rot (passed in)
void Mesh::Update(glm::vec3 pos, glm::vec3 rot)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), pos );
	modelMatrix = glm::rotate(modelMatrix, rot.y, glm::vec3(0,1,1));
}

/// Draw the object with a specified view + projection matrix, as well as a shader
void Mesh::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, Shader *shader)
{
	// Activate the shader program
	glUseProgram( shader->Program() );


		// Activate the VAO
		glBindVertexArray( VAO );

			// Send matrices to the shader as uniforms like this:
			glUniformMatrix4fv(shader->ModelMat(), 1, GL_FALSE, glm::value_ptr(modelMatrix) );
			glUniformMatrix4fv(shader->ViewMat(), 1, GL_FALSE, glm::value_ptr(viewMatrix) );
			glUniformMatrix4fv(shader->ProjMat(), 1, GL_FALSE, glm::value_ptr(projMatrix) );
			
			// Tell OpenGL to draw it
			glDrawArrays(GL_TRIANGLES, 0, numVertices);
			
		// Unbind VAO
		glBindVertexArray( 0 );
	
	// Reset program
	glUseProgram( 0 );
}