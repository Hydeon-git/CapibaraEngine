#include "ModuleFbxLoader.h"
#include "ModuleRenderer3D.h"
// Opengl + Glew

#include "glew.h";
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

// Assimp Includes + .lib
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"
#pragma comment (lib, "assimp-vc142-mt.lib")

ModuleFbxLoader::ModuleFbxLoader(Application* app, bool enabled) : Module(app, enabled)
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}
ModuleFbxLoader::~ModuleFbxLoader() {}

bool ModuleFbxLoader::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}

void ModuleFbxLoader::LoadFile(const char* filePath, std::vector<MeshData>& meshDataVec)
{
	const aiScene* scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);	
	
	if ((scene != nullptr) && (scene->HasMeshes()))
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		meshDataVec.resize(scene->mNumMeshes);
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			MeshData& meshData = meshDataVec[i];
			aiMesh* sceneMesh = scene->mMeshes[i];			

			meshData.num_meshes = scene->mNumMeshes;

			meshData.num_vertex = sceneMesh->mNumVertices;
			meshData.vertex = new float[meshData.num_vertex * 3];
			memcpy(meshData.vertex, sceneMesh->mVertices, sizeof(float) * meshData.num_vertex * 3);
			LOG("New mesh with %d vertices", meshData.num_vertex);

			// Copy faces
			if (sceneMesh->HasFaces())
			{
				meshData.num_index = sceneMesh->mNumFaces * 3;
				meshData.index = new uint[meshData.num_index]; // Assume each face is a triangle
				for (uint i = 0; i < sceneMesh->mNumFaces; ++i)
				{
					if (sceneMesh->mFaces[i].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&meshData.index[i * 3], sceneMesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}
				}
			}
			meshData.CreateBuffers();			
		}
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", filePath);
	}
}