#include "SoftwareCore/EventSystem.hpp"

void Core::EventSystem::SubscribeToEvent(EventCode code, OnEventFunc fnc, void* const listener)
{
	registeredEvents_[code][listener] = fnc;
}

void Core::EventSystem::UnsubscribeFromEvent(EventCode code, void* const listener)
{
	registeredEvents_[code].erase(listener);
}

void Core::EventSystem::SignalEvent(EventCode code, EventData context)
{
	for (const auto& listenerEntry : registeredEvents_[code])
	{
		listenerEntry.second(code, context);
	}
}
