#include "fbxLoader.h"
#include "ModuleRenderer3D.h"
#pragma comment (lib, "assimp-vc142-mt.lib")

fbxLoader::fbxLoader(bool enabled) 
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}
fbxLoader::~fbxLoader() {}

bool fbxLoader::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}

void fbxLoader::LoadFile(const char* filePath)
{
	const aiScene* scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	
	
	if ((scene != nullptr) && (scene->HasMeshes()))
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* sceneMesh = scene->mMeshes[i];			

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
			meshData.CreateMeshBuffers();
		}
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", filePath);
	}
}

