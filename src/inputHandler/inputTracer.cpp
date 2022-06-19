#pragma once
#include "inputTracer.h"
#include "utils.h"
const char* InputTraceConfigDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\custom";
void inputTracer::processUserInputTrace(userInputEvent a_userInput, bool isButtonDown) {
	if (!keyTraceMap_userEvent.contains(a_userInput)) {
		return;
	}
	if (isButtonDown) {
		//DEBUG("button down on event {}, adding spells", a_userInput);
		int i = 0;
		for (auto one_spell : keyTraceMap_userEvent[a_userInput]) {
			i++;
			utils::addSpellToPlayer(one_spell);
		}
		//DEBUG("added {} spells", i);
	}
	else {
		//DEBUG("button up on event {}, removing spells", a_userInput);
		int i = 0;
		for (auto one_spell : keyTraceMap_userEvent[a_userInput]) {
			i++;
			utils::removeSpellFromPlayer(one_spell);
		}
		//DEBUG("removed {} spells", i);
	}
}

void inputTracer::processIDInputTrace(IDEvent a_eventID, RE::INPUT_DEVICE a_device, bool isButtonDown) {
	switch (a_device) {
	case RE::INPUT_DEVICE::kGamepad:
		if (keyTraceMap_EventID_GamePad.contains(a_eventID)) {
			for (auto one_spell : keyTraceMap_EventID_GamePad[a_eventID]) {
				if (isButtonDown) {
					utils::addSpellToPlayer(one_spell);
				}
				else {
					utils::removeSpellFromPlayer(one_spell);
				}
				
			}
		}
		break;
	case RE::INPUT_DEVICE::kMouse:
		if (keyTraceMap_EventID_Mouse.contains(a_eventID)) {
			for (auto one_spell : keyTraceMap_EventID_Mouse[a_eventID]) {
				if (isButtonDown) {
					utils::addSpellToPlayer(one_spell);
				}
				else {
					utils::removeSpellFromPlayer(one_spell);
				}
			}
		}
		break;
	case RE::INPUT_DEVICE::kKeyboard:
		if (keyTraceMap_EventID_Keyboard.contains(a_eventID)) {
			for (auto one_spell : keyTraceMap_EventID_Keyboard[a_eventID]) {
				if (isButtonDown) {
					utils::addSpellToPlayer(one_spell);
				}
				else {
					utils::removeSpellFromPlayer(one_spell);
				}
			}
		}
		break;
	}
}

void inputTracer::loadInputTraceConfigs() {
	INFO("Loading custom input trace configurations...");
	int i = 0;
	if (std::filesystem::is_directory(InputTraceConfigDir)) {
		for (const auto& entry : std::filesystem::directory_iterator(InputTraceConfigDir)) { //iterates through all .ini files
			std::string pathStr = entry.path().string();
			INFO("Loading from {}", pathStr);
			const char* cstr = pathStr.c_str();
			loadInputTraceConfig(cstr);
			i++;
		}
		INFO("..done; loaded {} ini configs.", i);
	}
	else {
		ERROR("Error: input trace config directory not found");
	}
	
}

void inputTracer::loadInputTraceConfig(const char* a_iniPath) {
	CSimpleIniA ini;
	ini.SetMultiKey(true);
	ini.LoadFile(a_iniPath);
	loadUserInputTraceConfig(ini);
	loadIDInputTraceConfig(ini);
}


void inputTracer::loadUserInputTraceConfig(CSimpleIniA& a_ini) {
	auto readOneLine = [](std::string a_line)
	{
		INFO(a_line);
		auto vec = utils::tokenize(a_line);
		std::string userInput = vec[0];
		std::string formID = vec[1];
		std::string plugin = vec[2];
		RE::SpellItem* spell = gameDataUilts::getForm<RE::SpellItem>(RE::TESDataHandler::GetSingleton(), formID, plugin);
		auto it = keyTraceMap_userEvent.find(userInput);
		if (it != keyTraceMap_userEvent.end()) {
			it->second.push_back(spell);
		}
		else {
			keyTraceMap_userEvent.emplace(userInput, std::vector({ spell }));
		}
	};
	simpleIniUtils::apply(a_ini, "KeyTrace_userEvent", readOneLine);
}


void inputTracer::loadIDInputTraceConfig(CSimpleIniA& a_ini) {
	loadIDInputTraceConfig_GamePad(a_ini);
	loadIDInputTraceConfig_Keyboard(a_ini);
	loadIDInputTraceConfig_Mouse(a_ini);
}

void inputTracer::loadIDInputTraceConfig_Mouse(CSimpleIniA& a_ini) {
	auto readOneLine = [](std::string a_line)
	{
		INFO(a_line);
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		std::string formID = vec[1];
		std::string plugin = vec[2];
		RE::SpellItem* spell = gameDataUilts::getForm<RE::SpellItem>(RE::TESDataHandler::GetSingleton(), formID, plugin);
		auto it = keyTraceMap_EventID_Mouse.find(EventID);
		if (it != keyTraceMap_EventID_Mouse.end()) {
			it->second.push_back(spell);
		}
		else {
			keyTraceMap_EventID_Mouse.emplace(EventID, std::vector({ spell }));
		}
	};
	simpleIniUtils::apply(a_ini, "KeyTrace_EventID_Mouse", readOneLine);
}


void inputTracer::loadIDInputTraceConfig_GamePad(CSimpleIniA& a_ini) {
	auto readOneLine = [](std::string a_line)
	{
		INFO(a_line);
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		std::string formID = vec[1];
		std::string plugin = vec[2];
		RE::SpellItem* spell = gameDataUilts::getForm<RE::SpellItem>(RE::TESDataHandler::GetSingleton(), formID, plugin);
		auto it = keyTraceMap_EventID_GamePad.find(EventID);
		if (it != keyTraceMap_EventID_GamePad.end()) {
			it->second.push_back(spell);
		}
		else {
			keyTraceMap_EventID_GamePad.emplace(EventID, std::vector({ spell }));
		}
	};
	simpleIniUtils::apply(a_ini, "KeyTrace_EventID_GamePad", readOneLine);
}

void inputTracer::loadIDInputTraceConfig_Keyboard(CSimpleIniA& a_ini) {
	auto readOneLine = [](std::string a_line)
	{
		INFO(a_line);
		auto vec = utils::tokenize(a_line);
		uint32_t EventID = static_cast<uint32_t>(std::stoul(vec[0]));
		std::string formID = vec[1];
		std::string plugin = vec[2];
		RE::SpellItem* spell = gameDataUilts::getForm<RE::SpellItem>(RE::TESDataHandler::GetSingleton(), formID, plugin);
		auto it = keyTraceMap_EventID_Keyboard.find(EventID);
		if (it != keyTraceMap_EventID_Keyboard.end()) {
			it->second.push_back(spell);
		}
		else {
			keyTraceMap_EventID_Keyboard.emplace(EventID, std::vector({ spell }));
		}
	};
	simpleIniUtils::apply(a_ini, "KeyTrace_EventID_Keyboard", readOneLine);
}
