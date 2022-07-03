#include "inputEventHandler.h"
#include "inputHandler/movementInputTracer.h"
#include "inputHandler/inputTracer.h"
#include "inputHandler/animEvent.h"
#include "hasher.hpp"
#include "settings.h"


using EventType = RE::INPUT_EVENT_TYPE;
using DeviceType = RE::INPUT_DEVICE;
const auto ui = RE::UI::GetSingleton();

inline void processKeyTrace(RE::BSFixedString a_userEvent) {
	
}


inline void processAnimationEvent(RE::BSFixedString a_userEvent) {
	
}

void inputEventHandler::offsetInputKeyIndex(uint32_t& a_key, RE::INPUT_DEVICES::INPUT_DEVICE a_inputDevice) {
	switch (a_inputDevice) {
	case DeviceType::kMouse:
		a_key += kMouseOffset;
		break;
	case DeviceType::kKeyboard:
		a_key += kKeyboardOffset;
		break;
	case DeviceType::kGamepad:
		a_key = GetGamepadIndex((RE::BSWin32GamepadDevice::Key)a_key);
		break;
	default:
		return;
	}
}

void inputEventHandler::processEventID(RE::ButtonEvent* a_buttonEvent, bool isDown) {
	auto id = a_buttonEvent->idCode;
	auto device = a_buttonEvent->device.get();
	offsetInputKeyIndex(id, device);
	inputTracer::GetSingleton()->processIDInputTrace(id, device, isDown);
	if (isDown) {
		animEvent::GetSingleton()->processInput(id, device);
	}
}
void inputEventHandler::processUserEventTrace(RE::BSFixedString a_userEvent, bool isDown) {
	inputTracer::GetSingleton()->processUserInputTrace(static_cast<std::string>(a_userEvent), isDown);
}


EventResult inputEventHandler::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) {
	if (!a_event || RE::UI::GetSingleton()->GameIsPaused()) {
		return EventResult::kContinue;
	}

	for (auto one_event = *a_event; one_event; one_event = one_event->next) {

		
		if (one_event->GetEventType() != RE::INPUT_EVENT_TYPE::kButton) {//get rid of all none-button events.
			return EventResult::kContinue;
		}
		auto buttonEvent = static_cast<RE::ButtonEvent*>(one_event);
		bool isDown = buttonEvent->IsDown();
		if (!isDown && !buttonEvent->IsUp()) {  //only perform trace on downs/ups
			return EventResult::kContinue;
		}
		auto userEvent = one_event->QUserEvent();

		if (settings::bLogUserEvent) {
			RE::ConsoleLog::GetSingleton()->Print(userEvent.c_str());
		}
		if (settings::bToggleUserEventInputTrace) {
			processUserEventTrace(userEvent, isDown);
		}
		if (settings::bToggleEventIDInputTrace) {
			processEventID(buttonEvent, isDown);
		}
		
	}

	return EventResult::kContinue;

}

std::uint32_t inputEventHandler::GetGamepadIndex(RE::BSWin32GamepadDevice::Key a_key) {
	using Key = RE::BSWin32GamepadDevice::Key;

	std::uint32_t index;
	switch (a_key)
	{
	case Key::kUp:
		index = 0;
		break;
	case Key::kDown:
		index = 1;
		break;
	case Key::kLeft:
		index = 2;
		break;
	case Key::kRight:
		index = 3;
		break;
	case Key::kStart:
		index = 4;
		break;
	case Key::kBack:
		index = 5;
		break;
	case Key::kLeftThumb:
		index = 6;
		break;
	case Key::kRightThumb:
		index = 7;
		break;
	case Key::kLeftShoulder:
		index = 8;
		break;
	case Key::kRightShoulder:
		index = 9;
		break;
	case Key::kA:
		index = 10;
		break;
	case Key::kB:
		index = 11;
		break;
	case Key::kX:
		index = 12;
		break;
	case Key::kY:
		index = 13;
		break;
	case Key::kLeftTrigger:
		index = 14;
		break;
	case Key::kRightTrigger:
		index = 15;
		break;
	default:
		index = kInvalid;
		break;
	}

	return index != kInvalid ? index + kGamepadOffset : kInvalid;
}
