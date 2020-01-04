#pragma once

#include <array>
#include <glad/glad.h>

struct Event {};
struct ApplicationTerminateEvent : public Event {};
struct KeyboardStateBroadcastEvent : public Event
{
	KeyboardStateBroadcastEvent(const std::array<bool, 6>& keyboardState) : keyboardState(keyboardState) {}
	const std::array<bool, 6> keyboardState;
};
struct MouseMovedEvent : public Event
{
	MouseMovedEvent(const GLfloat xOffset, const GLfloat yOffset) : xOffset(xOffset), yOffset(yOffset) {}
	const GLfloat xOffset;
	const GLfloat yOffset;
};
struct FramebufferResizeEvent : public Event
{
	FramebufferResizeEvent(const int width, const int height) : width(width), height(height) {}
	int width;
	int height;
};