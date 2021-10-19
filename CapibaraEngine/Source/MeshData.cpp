#include "MeshData.h"

// OpenGL
#include "glew.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>



void MeshData::CreateMeshBuffers()
{
	// Initialization of the vertex and index from the mesh data
	// Vertex
	glGenBuffers(1, &id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * num_vertex * 3, vertex, GL_STATIC_DRAW);	

	// Index
	glGenBuffers(1, &id_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index, index, GL_STATIC_DRAW);	
}

void MeshData::DrawMesh()
{
	//BindElementBuffer
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, index);
}