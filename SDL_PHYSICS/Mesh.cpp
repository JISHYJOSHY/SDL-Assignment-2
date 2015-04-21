
#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>


/// Check to see if the shader has compiled
bool CheckShaderCompiled( GLint shader )
{
	GLint compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled )
	{
		GLsizei len;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete [] log;

		return false;
	}
	return true;
}

/// Constructor loads in a mesh file
Mesh::Mesh(std::string objFileName)
{
	// Initialise variables
	VAO = 0;
	shader = 0;
	shaderModelMatLocation = shaderViewMatLocation = shaderProjMatLocation = 0;

	objLoader.Load(objFileName);

	// Create the model
	InitialiseVAO();
	
	// Create the shaders
	InitialiseShaders();
}

Mesh::~Mesh()
{
	// TODO: destroy VAO, shaders etc
}

void Mesh::InitialiseVAO()
{
	// Creates one VAO
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
	numVertices = objLoader.GetMeshVertices().size();

	// stores data in the position buffer
	positionBuffer = 0;
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &objLoader.GetMeshVertices()[0], GL_STATIC_DRAW);
	
	// stores data in the normal buffer
	normalBuffer = 0;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &objLoader.GetMeshNormals()[0], GL_STATIC_DRAW);
	
	// stores data in the texture Coordinate buffer
	texCoordBuffer = 0;
	glGenBuffers(1, &texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec2), &objLoader.GetMeshTexCoords()[0], GL_STATIC_DRAW);

	// Unbind for neatness, it just makes life easier
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray( 0 );

	// Technically we can do this, because the enabled / disabled state is stored in the VAO
	glDisableVertexAttribArray(0);
}

void Mesh::InitialiseShaders()
{	
	// This is the vertex shader being loaded from file
	std::string VertexShaderCode = ReadFile("Shaders/basicVert.vert");
	
	// This is the fragment shader
	std::string FragShaderCode = ReadFile("Shaders/basicFrag.frag");

	// The 'program' stores the shaders
	shader = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader( GL_VERTEX_SHADER );
	// Give GL the source for it
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource( vShader, 1, &VertexSourcePointer, NULL );
	// Compile the shader
	glCompileShader( vShader );
	// Check it compiled and give useful output if it didn't work!
	if( !CheckShaderCompiled( vShader ) )
	{
		return;
	}
	// This links the shader to the program
	glAttachShader( shader, vShader );

	// Same for the fragment shader
	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
	char const* FragSourcePointer = FragShaderCode.c_str();
	glShaderSource( fShader, 1, &FragSourcePointer, NULL );
	glCompileShader( fShader );
	if( !CheckShaderCompiled( fShader ) )
	{
		return ;
	}
	glAttachShader( shader, fShader );

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( shader );
	// Check this worked
	GLint linked;
	glGetProgramiv( shader, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv( shader, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;

		return;
	}

	// We need to get the location of the uniforms in the shaders
	// This is so that we can send the values to them from the application
	// We do this in the following way: 
	shaderModelMatLocation = glGetUniformLocation( shader, "modelMat" );
	shaderViewMatLocation  = glGetUniformLocation( shader, "viewMat" );
	shaderProjMatLocation  = glGetUniformLocation( shader, "projMat" );

}

void Mesh::Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	// update the model matrix based on the 
	modelMatrix = glm::translate(glm::mat4(1.0f), position );

	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));

	modelMatrix = glm::scale(glm::mat4(1.0f), scale);
}

void Mesh::Draw(glm::mat4& viewMatrix, glm::mat4& projMatrix)
{
	// Ok, here I like to indent drawing calls - it's just a personal style, you may not like it and that's fine ;)
	// Generally you will need to be activating and deactivating OpenGL states
	// I just find it visually easier if the activations / deactivations happen at different tab depths
	// This can help when things get more complex

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	// Activate the shader program
	glUseProgram( shader );

		// Activate the VAO
		glBindVertexArray( VAO );

			// Send matrices to the shader as uniforms like this:
			glUniformMatrix4fv(shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix) );
			glUniformMatrix4fv(shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix) );
			glUniformMatrix4fv(shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix) );

			//send the diffuse texture to the shader
			int diffuseSampler = glGetUniformLocation(shader, "texSampler");
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseTexID);
			glUniform1i(diffuseSampler, 0);

			//vertex position data read in from obj file
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			//vertex normal data read in from obj file
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			//vertex texture coordinate data read in from obj file
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Tell OpenGL to draw it
			// Must specify the type of geometry to draw and the number of vertices
			glDrawArrays(GL_TRIANGLES, 0, numVertices);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

		// Unbind VAO
		glBindVertexArray( 0 );
	
	// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
	glUseProgram( 0 );
}



void Mesh::LoadTexture(const char* filename)
{	
	// load bmp through SDL
	SDL_Surface* image = SDL_LoadBMP(filename);
	
	// check if it has loaded
	if (!image)
	{
		std::cout << "FAILED : Cannot open file:"  << std::endl;
		return;
	}

	std::cout << "SUCCESS : Texture loaded" << std::endl;
	
	// use the SDL imported data to generate a texture through glew
	glGenTextures(1, &diffuseTexID);
	glBindTexture(GL_TEXTURE_2D, diffuseTexID);

	// BMP files are loaded in with the colour channels backwards, so we need to process it as a BGR instead of RGB
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	// OpenGL now has our image data, so we can free the loaded image
	SDL_FreeSurface(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
}

std::string Mesh::ReadFile(std::string fileName) {
	
	std::string result;

	std::ifstream stream(fileName, std::ios::in);
	if (stream.is_open()){
		std::string Line = "";
		while (getline(stream, Line))
			result += "\n" + Line;
		stream.close();
	}

	return result;
}