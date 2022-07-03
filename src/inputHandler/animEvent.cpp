#include "animEvent.h"
#include "utils.h"
void animEvent::loadConfigs() {

}

void animEvent::processAnimEventKey(animEventMap a_animEventMap, IDEvent a_event)
{
	auto it = a_animEventMap.find(a_event);
	if (it != a_animEventMap.end()) {
		for (auto& animEvent : *it->second) {
			utils::saeToPlayer(animEvent);
		}
	}
}

void animEvent::processAnimBoolFlipKey(animEventMap a_animEventMap, IDEvent a_event) {
	auto it = a_animEventMap.find(a_event);
	if (it != a_animEventMap.end()) {
		for (auto& gvb : *it->second) {
			utils::flipGraphVariableBoolForPc(gvb);
		}
	}
}

void animEvent::processInput(IDEvent a_eventID, RE::INPUT_DEVICE a_device)
{
	switch (a_device) {
	case RE::INPUT_DEVICE::kGamepad:
		processAnimEventKey(animEventMap_EventID_GamePad, a_eventID);
		processAnimBoolFlipKey(animBoolMap_EventID_GamePad, a_eventID);
		break;
	case RE::INPUT_DEVICE::kKeyboard:
		processAnimEventKey(animEventMap_EventID_Keyboard, a_eventID);
		processAnimBoolFlipKey(animBoolMap_EventID_Keyboard, a_eventID);
		break;
	case RE::INPUT_DEVICE::kMouse:
		processAnimEventKey(animEventMap_EventID_Mouse, a_eventID);
		processAnimBoolFlipKey(animBoolMap_EventID_Mouse, a_eventID);
		break;
	}
}
