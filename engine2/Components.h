#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Model.h"

struct RenderableComponent {};

struct MeshComponent
{
	std::shared_ptr<Model> cModel;
};

struct TransformComponent
{
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale{ 1.0f };
};

struct CameraComponent
{
	GLfloat yaw = 0.0f;
	GLfloat pitch = 0.0f;
	GLfloat fov = 45.0f;
	GLfloat nearClipPlane = 0.1f;
	GLfloat farClipPlane = 100.0f;
};

struct CameraControlComponent {};