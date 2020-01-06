#pragma once

#include <memory>
#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	// the trick to give resoures creation exclusive right to ResourceManager
	class Token
	{
	private:
		Token() {}
		friend class ResourceManager;
	};

	Material(Token, const std::string& path);
	Material(const Shader&) = delete;
	Material& operator=(const Material&) = delete;

	void bind();
	static void unbind();

private:
	std::shared_ptr<Texture> mDiffuseMap, mSpecularMap;
	std::shared_ptr<Shader> mShader;
};