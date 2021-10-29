#include "ModuleTextureLoader.h"

// DeviL
#include "il.h"
#include "ilu.h"
#include "ilut.h"
#include "devil_cpp_wrapper.hpp"

ModuleTextureLoader::ModuleTextureLoader(Application* app, bool enabled) : Module(app, enabled){}
ModuleTextureLoader::~ModuleTextureLoader(){}

void ModuleTextureLoader::LoadTexture(const char* texturePath)
{
	// Setup and load image with DeviL
	ILuint imageTexture;
	ilGenImages(1, &imageTexture);
	ilBindImage(imageTexture);
	ilLoadImage(texturePath);
	
	// Get image info
	ILuint width, height;
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	ILubyte* data = ilGetData();

	GLubyte texture = ilutGLBindTexImage();


}

bool ModuleTextureLoader::CleanUp()
{
	return true;
}