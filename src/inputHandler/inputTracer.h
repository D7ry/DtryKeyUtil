#pragma once
#pragma once
#include "lib/SimpleIni.h"
class inputTracer
{
public:
	using userInputEvent = std::string;
	using IDEvent = uint32_t;
	static inputTracer* GetSingleton() {
		static inputTracer singleton;
		return  std::addressof(singleton);
	}

	void loadInputTraceConfigs();

	void processUserInputTrace(userInputEvent a_userInput, bool isButtonDown);
	void processIDInputTrace(IDEvent a_eventID, RE::INPUT_DEVICE a_device, bool isButtonDown);

private:
	inline void processInputTrace(std::unordered_map<IDEvent, std::shared_ptr<std::vector<RE::SpellItem*>>> a_keyTraceMap, IDEvent a_eventID, bool isButtonDown);


	void loadInputTraceConfig(const char* a_iniPath);
	void loadUserInputTraceConfig(CSimpleIniA& a_ini);
	void loadIDInputTraceConfig(CSimpleIniA& a_ini);

	void loadIDInputTraceConfig_Mouse(CSimpleIniA& a_ini);
	void loadIDInputTraceConfig_Keyboard(CSimpleIniA& a_ini);
	void loadIDInputTraceConfig_GamePad(CSimpleIniA& a_ini);

	std::unordered_map<userInputEvent, std::shared_ptr<std::vector<RE::SpellItem*>>> keyTraceMap_userEvent;
	std::unordered_map<IDEvent, std::shared_ptr<std::vector<RE::SpellItem*>>> keyTraceMap_EventID_Keyboard;
	std::unordered_map<IDEvent, std::shared_ptr<std::vector<RE::SpellItem*>>> keyTraceMap_EventID_Mouse;
	std::unordered_map<IDEvent, std::shared_ptr<std::vector<RE::SpellItem*>>> keyTraceMap_EventID_GamePad;
};
