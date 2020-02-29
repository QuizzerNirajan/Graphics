<<<<<<< HEAD
#ifndef MESH_H
#define MESH_H

#include "includes.h"
#include "Shader.h"
#include <vector>

using namespace std;
=======
#pragma once

#include "includes.h"
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
>>>>>>> dbe5e60b2a3a3da52d99745725cc6f7a32c6317f

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

<<<<<<< HEAD
struct Texture {
	unsigned int id;
	string type;
	string path;
};
=======
>>>>>>> dbe5e60b2a3a3da52d99745725cc6f7a32c6317f

class Mesh {
public:
	/*  Mesh Data  */
<<<<<<< HEAD
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	/*  Functions  */
	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

=======
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	VertexArray va;

	/*  Functions  */
	// constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		:vertices(vertices), indices(indices), textures(textures), va(),vb(&vertices[0], vertices.size() * sizeof(Vertex)),ib(&indices[0], indices.size())
	{
	
>>>>>>> dbe5e60b2a3a3da52d99745725cc6f7a32c6317f
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
<<<<<<< HEAD
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			string number;
			string name = textures[i].type;
=======
			/*glActiveTexture(GL_TEXTURE0 + i);*/ // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].GetType();
>>>>>>> dbe5e60b2a3a3da52d99745725cc6f7a32c6317f
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to stream

			// now set the sampler to the correct texture unit
<<<<<<< HEAD
			glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
=======
			/*glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);*/
			shader.setInt((name + number).c_str(), i);
			// and finally bind the texture
		/*	glBindTexture(GL_TEXTURE_2D, textures[i].GetID());*/
			textures[i].Bind(i);
		}

		va.Bind();

>>>>>>> dbe5e60b2a3a3da52d99745725cc6f7a32c6317f
	}

private:
	/*  Render data  */
	unsigned int VBO, EBO;
<<<<<<< HEAD

=======
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
>>>>>>> dbe5e60b2a3a3da52d99745725cc6f7a32c6317f
	/*  Functions    */
	// initializes all the buffer objects/arrays
	void setupMesh()
	{
<<<<<<< HEAD
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

		glBindVertexArray(0);
	}
};
#endif
=======
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
>>>>>>> dbe5e60b2a3a3da52d99745725cc6f7a32c6317f
