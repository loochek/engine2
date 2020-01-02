#pragma once

struct Event {};
struct ApplicationTerminateEvent : public Event {};
struct KeyPressedEvent : public Event
{
	KeyPressedEvent(int key) : key(key) {}
	int key;
};
struct KeyReleasedEvent : public Event
{
	KeyReleasedEvent(int key) : key(key) {}
	int key;
};