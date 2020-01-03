#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"

struct RenderableComponent {};

struct MeshComponent
{
	std::shared_ptr<Mesh> cMesh;
};

struct TransformComponent
{
	glm::vec3 translation;
	glm::vec3 rotationAxis{ 1.0f, 0.0f, 0.0f };
	GLfloat rotationAngle = 0.0f;
	glm::vec3 scale{ 1.0f };
};

struct CameraComponent
{
	GLfloat yaw = 0.0f;
	GLfloat pitch = 0.0f;
};

struct CameraControlComponent {};