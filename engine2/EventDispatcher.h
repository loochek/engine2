#pragma once

#include <typeindex>
		
#include <map>
#include <list>
#include "Event.h"

class HandlerFunctionBase
{
public:
	// Call the member function
	void exec(Event* event)
	{
		call(event);
	}
private:
	// Implemented by MemberFunctionHandler
	virtual void call(Event* event) = 0;
};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
	typedef void (T::* MemberFunction)(EventType*);

	MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};

	void call(Event* event)
	{
		// Cast event to the correct type and call member function
		(instance->*memberFunction)(static_cast<EventType*>(event));
	}
private:
	// Pointer to class instance
	T* instance;

	// Pointer to member function
	MemberFunction memberFunction;
};

typedef std::list<HandlerFunctionBase*> HandlerList;

class EventDispatcher
{
public:
	static EventDispatcher& getInstance()
	{
		static EventDispatcher singleton;
		return singleton;
	}

	template<typename EventType>
	void emit(EventType* event)
	{
		HandlerList* handlers = mSubscriptions[typeid(EventType)];
		if (handlers == nullptr)
			return;
		for (auto& handler : *handlers)
			if (handler != nullptr)
				handler->exec(event);
	}

	template<class T, class EventType>
	void subscribe(T* instance, void (T::* memberFunction)(EventType*))
	{
		HandlerList* handlers = mSubscriptions[typeid(EventType)];

		if (handlers == nullptr)
		{
			handlers = new HandlerList();
			mSubscriptions[typeid(EventType)] = handlers;
		}
		handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
	}

private:
	std::map<std::type_index, std::list<HandlerFunctionBase*>*> mSubscriptions;

	EventDispatcher() {}                                      // Private constructor
	~EventDispatcher() {}
	EventDispatcher(const EventDispatcher&);                 // Prevent copy-construction
	EventDispatcher& operator=(const EventDispatcher&);      // Prevent assignment
};