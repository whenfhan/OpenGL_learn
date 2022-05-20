#pragma once

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "stb_image.h"
#include <string>
#include <vector>
#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
	Model(const char* path, bool gamma = false);
	void Draw(Shader shader);
private:
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* name, std::string dir);

private:
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
	bool gammaCorrection;
};

