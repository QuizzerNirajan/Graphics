
#pragma once

#include "includes.h"
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};


class Mesh {
public:
	/*  Mesh Data  */

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	VertexArray va;

	/*  Functions  */
	// constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		:vertices(vertices), indices(indices), textures(textures), va(),vb(&vertices[0], vertices.size() * sizeof(Vertex)),ib(&indices[0], indices.size())
	{
	
		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	// render the mesh
	void Draw(Shader shader)
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{

			/*glActiveTexture(GL_TEXTURE0 + i);*/ // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].GetType();

			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to stream

			// now set the sampler to the correct texture unit

			/*glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);*/
			shader.setInt((name + number).c_str(), i);
			// and finally bind the texture
		/*	glBindTexture(GL_TEXTURE_2D, textures[i].GetID());*/
			textures[i].Bind(i);
		}

		va.Bind();
	}

private:
	/*  Render data  */
	unsigned int VBO, EBO;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	/*  Functions    */
	// initializes all the buffer objects/arrays
	void setupMesh()
	{

		layout.Push<float>(3);//Positions
		layout.Push<float>(3);//Normals
		layout.Push<float>(2);//TexCoordinates
		layout.Push<float>(3);//Tangents
		layout.Push<float>(3);//Bitangents
		
		va.AddBuffer(vb, layout);

		ib = IndexBuffer(&indices[0], indices.size());
		va.Bind();
		
	}
};

