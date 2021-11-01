#include "MeshComponent.h"

// OpenGL
#include "glew.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

void MeshComponent::CreateMeshBuffers()
{
	// Initialization of the vertex and index from the mesh data
	// Vertex
	glGenBuffers(1, &idVertex);
	glBindBuffer(GL_ARRAY_BUFFER, idVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertex * 3, vertex, GL_STATIC_DRAW);

	// Index
	glGenBuffers(1, &idIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * numIndex, index, GL_STATIC_DRAW);	

	// Textures
	glGenBuffers(1, &idTexture);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idTexture);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numVertex * 2, textures, GL_STATIC_DRAW);
}

bool MeshComponent::DrawMesh()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, idVertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, idTexture);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glBindTexture(GL_TEXTURE_2D, idTexture);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIndex);

	glDrawElements(GL_TRIANGLES, numIndex, GL_UNSIGNED_INT, NULL);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//--Disables States--//
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return true;
}
