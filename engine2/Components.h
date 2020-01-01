#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"

struct RenderableComponent {};

struct MeshComponent
{
	Mesh cMesh;
};