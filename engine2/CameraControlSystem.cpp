#include "CameraControlSystem.h"
#include "ObjectController.h"
#include <GLFW/glfw3.h>
#include <iostream>

int CameraControlSystem::init()
{
	EventDispatcher::getInstance().subscribe(this, &CameraControlSystem::onKeyboardStateBroadcastEvent);
	EventDispatcher::getInstance().subscribe(this, &CameraControlSystem::onMouseMovedEvent);
	return 0;
}

void CameraControlSystem::update(GLfloat elapsedTime)
{
	for (auto i : mEntities)
	{
		CameraComponent& camera = ObjectController::getInstance().getComponent<CameraComponent>(i);
		TransformComponent& cameraTransform = ObjectController::getInstance().getComponent<TransformComponent>(i);
		GLfloat cameraSpeed = 0.05f;
		
		camera.pitch += mMouseYOffset * 0.3;
		camera.yaw += mMouseXOffset * 0.3;

		if (camera.yaw > 360.0f)
			camera.yaw -= 360.0f;
		if (camera.yaw < 0)
			camera.yaw += 360.0f;

		if (camera.pitch > 89.0f)
			camera.pitch = 89.0f;
		if (camera.pitch < -89.0f)
			camera.pitch = -89.0f;
		glm::vec3 cameraFront;
		cameraFront.x = cos(glm::radians(camera.pitch)) * cos(glm::radians(camera.yaw));
		cameraFront.y = sin(glm::radians(camera.pitch));
		cameraFront.z = cos(glm::radians(camera.pitch)) * sin(glm::radians(camera.yaw));
		cameraFront = glm::normalize(cameraFront);

		if (mKeys[1])
			cameraTransform.translation += cameraSpeed * cameraFront;
		if (mKeys[3])
			cameraTransform.translation -= cameraSpeed * cameraFront;
		if (mKeys[2])
			cameraTransform.translation -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
		if (mKeys[4])
			cameraTransform.translation += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
	}
}

void CameraControlSystem::shutdown()
{
}

void CameraControlSystem::onKeyboardStateBroadcastEvent(const KeyboardStateBroadcastEvent& event)
{
	mKeys = event.keyboardState;
}

void CameraControlSystem::onMouseMovedEvent(const MouseMovedEvent& event)
{
	mMouseXOffset = event.xOffset;
	mMouseYOffset = event.yOffset;
}