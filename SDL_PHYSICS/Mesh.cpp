#include "Mesh.h"

#include <fstream>
#include <algorithm>

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
}

Mesh::~Mesh(void)
{
}

void Mesh::LoadMesh(std::string filename)
{
		// Creates one VAO
	glGenVertexArrays( 1, &VAO );
	// 'Binding' something makes it the current one we are using
	// This is like activating it, so that subsequent function calls will work on this item
	glBindVertexArray( VAO );

	// OBJECT LOADER
	std::ifstream file(filename);
	unsigned int faceNum = 0;

	while(!file.eof())
	{
		char line[256];

		file.getline(line, 256);

		// if the line begins with a 'v', it is data we can use
		if(line[0] == 'v')
		{
			float a, b, c;

			// if the next char is 'n', we have a Vertex Normal
			if(line[1] == 'n')
			{
				sscanf(line, "vn %f %f %f", &a, &b, &c);
				normalsVector.push_back(glm::vec3(a, b, c));				
			}
			// if the next char is 't', we have a Vertex Texture
			else if(line[1] == 't')
			{

			}
			// else we just have the vertex position
			else
			{				
				sscanf(line, "v %f %f %f", &a, &b, &c);
				verticesVector.push_back(glm::vec3(a, b, c));
			}
		}
		/*
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                         "Missing file",
                         "File is missing. Please reinstall the program.",
                         NULL);
		*/

		if(line[0] == 'f')
		{
			// face, facenumber, facepart (vertex / texture / normal)
			int f1a = 1, f1b = 1, f1c = 1, f2a = 1, f2b = 1, f2c = 1, f3a = 1, f3b = 1, f3c = 1, f4a = 1, f4b = 1, f4c = 1;

			std::string lineS = std::string(line);

			// OBJ has 3 face definitions; Vertex/Texture/Normal, Vertex//Normal, Vertex, so we need to find which one this file type has

			// Firstly we check if the face is a Quad or a Tri
			if(count(lineS.begin(), lineS.end(), ' ') == 4)
			{
				// we check the format of the face
				if(lineS.find("//") != std::string::npos)
				{
					sscanf(line, "f %d//%d %d//%d %d//%d %d//%d", &f1a, &f1c, &f2a, &f2c, &f3a, &f3c, &f4a, &f4c);
				}
				else if(lineS.find("/") != std::string::npos)
				{
					sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &f1a, &f1b, &f1c, &f2a, &f2b, &f2c, &f3a, &f3b, &f3c, &f4a, &f4b, &f4c);
				}
				else
				{
					sscanf(line, "f %d %d %d %d", &f1a, &f2a, &f3a, &f4a);
				}

				faces.push_back(Face(f1a, f1b, f1c, true));
			faceNum++;
				faces.push_back(Face(f2a, f2b, f2c, true));
			faceNum++;
				faces.push_back(Face(f3a, f3b, f3c, true));
			faceNum++;
				faces.push_back(Face(f4a, f4b, f4c, true));
			}
			else
			{
				// we check the format of the face
				if(lineS.find("//") != std::string::npos)
				{
					sscanf(line, "f %d//%d %d//%d %d//%d", &f1a, &f1c, &f2a, &f2c, &f3a, &f3c);
				}
				else if(lineS.find("/") != std::string::npos)
				{
					sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1a, &f1b, &f1c, &f2a, &f2b, &f2c, &f3a, &f3b, &f3c);
				}
				else
				{
					sscanf(line, "f %d %d %d", &f1a, &f2a, &f3a);
				}

				faces.push_back(Face(f1a, f1b, f1c, false));
			faceNum++;
				faces.push_back(Face(f2a, f2b, f2c, false));
			faceNum++;
				faces.push_back(Face(f3a, f3b, f3c, false));
			}

			faceNum++;
		}
	}

	int fSize = faces.size();
	for(int i = 0; i < fSize;)
	{		
		if(faces[i].quad)
		{				
			vertices.push_back(verticesVector[faces[i].vertex - 1]);
			//normals.push_back(normalsVector[faces[i].normal - 1]);

			if(i + 1 < fSize)
			{
				vertices.push_back(verticesVector[faces[i + 1].vertex - 1]);
				//normals.push_back(normalsVector[faces[i + 1].normal - 1]);
			}
			if(i + 2 < fSize)
			{
				vertices.push_back(verticesVector[faces[i + 2].vertex - 1]);
				//normals.push_back(normalsVector[faces[i + 2].normal - 1]);
			}
			vertices.push_back(verticesVector[faces[i].vertex - 1]);
			//normals.push_back(normalsVector[faces[i].normal - 1]);
			if(i + 2 < fSize)
			{
				vertices.push_back(verticesVector[faces[i + 2].vertex - 1]);
				//normals.push_back(normalsVector[faces[i + 2].normal - 1]);
			}
			if(i + 3 < fSize)
			{
				vertices.push_back(verticesVector[faces[i + 3].vertex - 1]);
				//normals.push_back(normalsVector[faces[i + 3].normal - 1]);
			}

			i += 4;
		}
		else
		{			

			vertices.push_back(verticesVector[faces[i].vertex - 1]);
		//	normals.push_back(normalsVector[faces[i].normal - 1]);

			if(i + 1 < fSize)
			{
				vertices.push_back(verticesVector[faces[i + 1].vertex - 1]);
				//normals.push_back(normalsVector[faces[i + 1].normal - 1]);
			}
			if(i + 2 < fSize)
			{
				vertices.push_back(verticesVector[faces[i + 2].vertex - 1]);
				//normals.push_back(normalsVector[faces[i + 2].normal - 1]);
			}

			i += 3;
		}
	}

	// Number of vertices in above data
	numVertices = vertices.size();
	
	std::vector<float> vertFloats;
	std::vector<float> normalFloats;

	for(int i = 0; i < numVertices; i++)
	{
		vertFloats.push_back(vertices[i].x);
		vertFloats.push_back(vertices[i].y);
		vertFloats.push_back(vertices[i].z);

		normalFloats.push_back(normals[i].x);
		normalFloats.push_back(normals[i].y);
		normalFloats.push_back(normals[i].z);
	}

	float* vertex = vertFloats.data();
	float* normal = normalFloats.data();

	// END OBJECT LOADER

	// Variable for storing a VBO
	GLuint positionBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &positionBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, vertex, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	// (We will look at this properly in the lectures)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(0);
	
	// Normal data for our incomplete cube
	// Each entry is the normal for the corresponding vertex in the position data above

	// Variable for storing a VBO
	GLuint normalBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &normalBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, normal, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(1);	

	// Unbind for neatness, it just makes life easier
	// As a general tip, especially as you're still learning, for each function that needs to do something specific try to return OpenGL in the state you found it in
	// This means you will need to set the states at the beginning of your function and set them back at the end
	// If you don't do this, your function could rely on states being set elsewhere and it's easy to lose track of this as your project grows
	// If you then change the code from elsewhere, your current code could mysteriously stop working properly!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray( 0 );

	// Technically we can do this, because the enabled / disabled state is stored in the VAO
	glDisableVertexAttribArray(0);

}
/// Update the mesh position and rotation based on an objects pos + rot (passed in)
void Mesh::Update(glm::vec3 pos, glm::vec3 rot)
{
	// Build the model matrix!
	// First we start with an identity matrix
	// This is created with the command: glm::mat4(1.0f)
	// Next, we translate this matrix according to the object's _position vector:
	modelMatrix = glm::translate(glm::mat4(1.0f), pos );
	// Next, we rotate this matrix in the y-axis by the object's y-rotation:
	modelMatrix = glm::rotate(modelMatrix, rot.y, glm::vec3(0,1,0) );
	// And there we go, model matrix is ready!
}

/// Draw the object with a specified view + projection matrix, as well as a shader
void Mesh::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, Shader *shader)
{
	// Ok, here I like to indent drawing calls - it's just a personal style, you may not like it and that's fine ;)
	// Generally you will need to be activating and deactivating OpenGL states
	// I just find it visually easier if the activations / deactivations happen at different tab depths
	// This can help when things get more complex

	// Activate the shader program
	glUseProgram( shader->Program() );

		// Activate the VAO
		glBindVertexArray( VAO );

			// Send matrices to the shader as uniforms like this:
			glUniformMatrix4fv(shader->ModelMat(), 1, GL_FALSE, glm::value_ptr(modelMatrix) );
			glUniformMatrix4fv(shader->ViewMat(), 1, GL_FALSE, glm::value_ptr(viewMatrix) );
			glUniformMatrix4fv(shader->ProjMat(), 1, GL_FALSE, glm::value_ptr(projMatrix) );


			// Tell OpenGL to draw it
			// Must specify the type of geometry to draw and the number of vertices
			glDrawArrays(GL_TRIANGLES, 0, numVertices);
			
		// Unbind VAO
		glBindVertexArray( 0 );
	
	// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
	glUseProgram( 0 );
}