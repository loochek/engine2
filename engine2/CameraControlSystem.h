#pragma once

#include "System.h"
#include "Components.h"
#include "EventDispatcher.h"
#include <glm/glm.hpp>
#include <array>

class CameraControlSystem : public System
{
public:
	int init();
	void update(GLfloat elapsedTime);
	void shutdown();
private:
	std::array<bool, 5> mKeys;
	GLfloat mMouseXOffset;
	GLfloat mMouseYOffset;
	void onKeyboardStateBroadcastEvent(const KeyboardStateBroadcastEvent& event);
	void onMouseMovedEvent(const MouseMovedEvent& event);
};	