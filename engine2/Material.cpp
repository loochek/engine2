#include "Material.h"
#include "ResourceManager.h"
#include <fstream>

Material::Material(Token, const std::string& path)
{
	std::ifstream materialFile(path);
	while (!materialFile.eof())
	{
		std::string param;
		materialFile >> param;
		if (param == "Shader")
		{
			std::string shaderName;
			materialFile >> shaderName;
			mShader = ResourceManager::getInstance().getShader(shaderName);
		}
		else if (param == "DiffuseMap")
		{
			std::string diffMapName;
			materialFile >> diffMapName;
			mDiffuseMap = ResourceManager::getInstance().getTexture(diffMapName);
		}
		else if (param == "SpecularMap")
		{
			std::string specMapName;
			materialFile >> specMapName;
			mSpecularMap = ResourceManager::getInstance().getTexture(specMapName);
		}
	}
	materialFile.close();
}

void Material::bind()
{
	mShader->bind();
	mShader->setInt("texture_diffuse", 0);
	mShader->setInt("texture_specular", 1);
	if (mDiffuseMap)
		mDiffuseMap->bind(0);
	if (mSpecularMap)
		mSpecularMap->bind(1);
}

void Material::unbind()
{
	Texture::unbind(0);
	Texture::unbind(1);
	Shader::unbind();
}