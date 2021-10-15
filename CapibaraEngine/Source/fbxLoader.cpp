#include "fbxLoader.h"


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

void fbxLoader::LoadFile(char filePath[])
{	
	const aiScene* scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	vertexData vData;
	
	if ((scene != nullptr) && (scene->HasMeshes()))
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* sceneMesh = scene->mMeshes[i];			

			vData.num_vertex = sceneMesh->mNumVertices;
			vData.vertex = new float[vData.num_vertex * 3];
			memcpy(vData.vertex, sceneMesh->mVertices, sizeof(float) * vData.num_vertex * 3);
			LOG("New mesh with %d vertices", vData.num_vertex);

			// Copy faces
			if (sceneMesh->HasFaces())
			{
				vData.num_index = sceneMesh->mNumFaces * 3;
				vData.index = new uint[vData.num_index]; // Assume each face is a triangle
				for (uint i = 0; i < sceneMesh->mNumFaces; ++i)
				{
					if (sceneMesh->mFaces[i].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}						
					else
					{
						memcpy(&vData.index[i * 3], sceneMesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}						
				}
			}
		}		
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", filePath);
	}
	

}
