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
			utils::flipGraphVariableBoolForPlayer(gvb);
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

void animEvent::loadIDAnimEventConfig_Mouse(CSimpleIniA& a_ini)
{
	auto readOneLine = [](std::string a_line) {
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		RE::BSFixedString ae = vec[1];

		auto ptr = animEvent::GetSingleton();
		auto it = ptr->animEventMap_EventID_Mouse.find(EventID);
		if (it != ptr->animEventMap_EventID_Mouse.end()) {
			it->second->push_back(ae);
		} else {
			auto aeVec = std::make_shared<std::vector<RE::BSFixedString>>();
			aeVec->push_back(ae);
			ptr->animEventMap_EventID_Mouse.insert({ EventID, aeVec });
		}
	};
	simpleIniUtils::apply(a_ini, "AnimEvent_EventID_Mouse", readOneLine);
}

void animEvent::loadIDAnimEventConfig_Keyboard(CSimpleIniA& a_ini)
{
	auto readOneLine = [](std::string a_line) {
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		RE::BSFixedString ae = vec[1];

		auto ptr = animEvent::GetSingleton();
		auto it = ptr->animEventMap_EventID_Keyboard.find(EventID);
		if (it != ptr->animEventMap_EventID_Keyboard.end()) {
			it->second->push_back(ae);
		} else {
			auto aeVec = std::make_shared<std::vector<RE::BSFixedString>>();
			aeVec->push_back(ae);
			ptr->animEventMap_EventID_Keyboard.insert({ EventID, aeVec });
		}
	};
	simpleIniUtils::apply(a_ini, "AnimEvent_EventID_Keyboard", readOneLine);
}

void animEvent::loadIDAnimEventConfig_GamePad(CSimpleIniA& a_ini)
{
	auto readOneLine = [](std::string a_line) {
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		RE::BSFixedString ae = vec[1];

		auto ptr = animEvent::GetSingleton();
		auto it = ptr->animEventMap_EventID_GamePad.find(EventID);
		if (it != ptr->animEventMap_EventID_GamePad.end()) {
			it->second->push_back(ae);
		} else {
			auto aeVec = std::make_shared<std::vector<RE::BSFixedString>>();
			aeVec->push_back(ae);
			ptr->animEventMap_EventID_Mouse.insert({ EventID, aeVec });
		}
	};
	simpleIniUtils::apply(a_ini, "AnimEvent_EventID_GamePad", readOneLine);
}

void animEvent::loadIDAnimBoolConfig_Mouse(CSimpleIniA& a_ini)
{
	auto readOneLine = [](std::string a_line) {
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		RE::BSFixedString ae = vec[1];

		auto ptr = animEvent::GetSingleton();
		auto it = ptr->animBoolMap_EventID_Mouse.find(EventID);
		if (it != ptr->animBoolMap_EventID_Mouse.end()) {
			it->second->push_back(ae);
		} else {
			auto aeVec = std::make_shared<std::vector<RE::BSFixedString>>();
			aeVec->push_back(ae);
			ptr->animBoolMap_EventID_Mouse.insert({ EventID, aeVec });
		}
	};
	simpleIniUtils::apply(a_ini, "AnimBool_EventID_Mouse", readOneLine);

}

void animEvent::loadIDAnimBoolConfig_Keyboard(CSimpleIniA& a_ini)
{
	auto readOneLine = [](std::string a_line) {
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		RE::BSFixedString ae = vec[1];

		auto ptr = animEvent::GetSingleton();
		auto it = ptr->animBoolMap_EventID_Keyboard.find(EventID);
		if (it != ptr->animBoolMap_EventID_Keyboard.end()) {
			it->second->push_back(ae);
		} else {
			auto aeVec = std::make_shared<std::vector<RE::BSFixedString>>();
			aeVec->push_back(ae);
			ptr->animBoolMap_EventID_Keyboard.insert({ EventID, aeVec });
		}
	};
	simpleIniUtils::apply(a_ini, "AnimBool_EventID_Keyboard", readOneLine);
}

void animEvent::loadIDAnimBoolConfig_GamePad(CSimpleIniA& a_ini)
{
	auto readOneLine = [](std::string a_line) {
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		RE::BSFixedString ae = vec[1];

		auto ptr = animEvent::GetSingleton();
		auto it = ptr->animBoolMap_EventID_GamePad.find(EventID);
		if (it != ptr->animBoolMap_EventID_GamePad.end()) {
			it->second->push_back(ae);
		} else {
			auto aeVec = std::make_shared<std::vector<RE::BSFixedString>>();
			aeVec->push_back(ae);
			ptr->animBoolMap_EventID_GamePad.insert({ EventID, aeVec });
		}
	};
	simpleIniUtils::apply(a_ini, "AnimBool_EventID_GamePad", readOneLine);
}
