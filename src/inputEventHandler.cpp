#include "inputEventHandler.h"
#include "movementInputTracer.h"
#include "hasher.hpp"
#include "settings.h"

inline void processKeyTrace(RE::BSFixedString a_userEvent) {
	
}


inline void processAnimationEvent(RE::BSFixedString a_userEvent) {
	
}


inline void tryTraceMovementInputEvent(RE::InputEvent* a_event, RE::BSFixedString a_userEvent) {
	switch (hash(static_cast<std::string>(a_userEvent))) {
	case "Forward"_h: movementInputTracer::GetSingleton()->onKeyBoardMovement(static_cast<RE::ButtonEvent*>(a_event), movementInputTracer::movementDirection::forward); break;
	case "Back"_h: movementInputTracer::GetSingleton()->onKeyBoardMovement(static_cast<RE::ButtonEvent*>(a_event), movementInputTracer::movementDirection::back); break;
	case "Strafe Right"_h: movementInputTracer::GetSingleton()->onKeyBoardMovement(static_cast<RE::ButtonEvent*>(a_event), movementInputTracer::movementDirection::right); break;
	case "Strafe Left"_h: movementInputTracer::GetSingleton()->onKeyBoardMovement(static_cast<RE::ButtonEvent*>(a_event), movementInputTracer::movementDirection::left); break;
	case "Move"_h:
		if (a_event->GetDevice() == RE::INPUT_DEVICE::kGamepad) {
			movementInputTracer::GetSingleton()->onThumbStickMovement(static_cast<RE::ThumbstickEvent*>(a_event)); break;
		}
	}
}


using EventType = RE::INPUT_EVENT_TYPE;
using DeviceType = RE::INPUT_DEVICE;
const auto ui = RE::UI::GetSingleton();
EventResult inputEventHandler::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) {
	if (!a_event || RE::UI::GetSingleton()->GameIsPaused()) {
		return EventResult::kContinue;
	}



	for (auto one_event = *a_event; one_event; one_event = one_event->next) {
		switch (one_event->GetEventType()) {
		case EventType::kChar:
		case EventType::kMouseMove:
		case EventType::kDeviceConnect:
		case EventType::kKinect: return EventResult::kContinue;
		}

		auto userEvent = one_event->QUserEvent();
		if (settings::bLogUserEvent) {
			RE::ConsoleLog::GetSingleton()->Print(userEvent.c_str());
		}

		if (settings::bToggleMovementInputTrace) {
			tryTraceMovementInputEvent(one_event, userEvent);
		}
		
		if (one_event->GetEventType() == RE::INPUT_EVENT_TYPE::kButton) {

		}
		auto button = static_cast<RE::ButtonEvent*>(one_event);
		if (button) {
			auto key = button->idCode;
			switch (button->device.get()) {
			case DeviceType::kMouse:
				key += kMouseOffset;
				break;
			case DeviceType::kKeyboard:
				key += kKeyboardOffset;
				break;
			case DeviceType::kGamepad:
				key = GetGamepadIndex((RE::BSWin32GamepadDevice::Key)key);
				break;
			default:
				continue;
			}

			auto it_keyTrace = settings::keyTraceMap_u.find(static_cast<std::string>(userEvent));
			while (it_keyTrace != settings::keyTraceMap_u.end()) {
				//do stuff
				it_keyTrace++;
			}

			/*
			if (key == settings::uAltBlockKey || button->QUserEvent() == "Left Attack/Block") {
				if (button->IsDown()) {
					blockHandler::GetSingleton()->onBlockKeyDown();
				}
				else if (button->IsUp()) {
					blockHandler::GetSingleton()->onBlockKeyUp();
				}
			}*/
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