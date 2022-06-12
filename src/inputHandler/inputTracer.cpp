#pragma once
#include "inputTracer.h"
#include "utils.h"
const char* InputTraceConfigDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\custom";
void inputTracer::processUserInputTrace(userInputEvent a_userInput, bool isButtonDown) {
	if (!keyTraceMap_u.contains(a_userInput)) {
		return;
	}
	if (isButtonDown) {
		for (auto one_spell : keyTraceMap_u[a_userInput]) {
			utils::addSpellToPlayer(one_spell);
		}
	}
	else {
		for (auto one_spell : keyTraceMap_u[a_userInput]) {
			utils::removeSpellFromPlayer(one_spell);
		}
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
	auto readOneLine = [](std::string a_line)
	{
		INFO(a_line);
		auto vec = utils::tokenize(a_line);
		std::string userInput = vec[0];
		std::string formID = vec[1];
		std::string plugin = vec[2];
		RE::SpellItem* spell = gameDataUilts::getForm<RE::SpellItem>(RE::TESDataHandler::GetSingleton(), formID, plugin);
		auto it = keyTraceMap_u.find(userInput);
		if (it != keyTraceMap_u.end()) {
			it->second.push_back(spell);
		}
		else {
			keyTraceMap_u.emplace(userInput, std::vector({ spell }));
		}
	};
	simpleIniUtils::apply(ini, "KeyTrace_userEvent", readOneLine);
}

void inputTracer::loadUserInputConfig(CSimpleIniA& a_ini) {

}
