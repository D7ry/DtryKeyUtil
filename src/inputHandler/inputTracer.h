#pragma once
#pragma once
#include "lib/robin_hood.h"
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

	void processUserInputTrace(userInputEvent a_userInput, bool isButtonDown);
	void processIDInputTrace(IDEvent a_eventID, RE::INPUT_DEVICE a_device, bool isButtonDown);
	void loadInputTraceConfigs();
private:
	void loadInputTraceConfig(const char* a_iniPath);
	void loadUserInputTraceConfig(CSimpleIniA& a_ini);
	void loadIDInputTraceConfig(CSimpleIniA& a_ini);

	void loadIDInputTraceConfig_Mouse(CSimpleIniA& a_ini);
	void loadIDInputTraceConfig_Keyboard(CSimpleIniA& a_ini);
	void loadIDInputTraceConfig_GamePad(CSimpleIniA& a_ini);

	static robin_hood::unordered_map<userInputEvent, std::vector<RE::SpellItem*>> keyTraceMap_userEvent;
	static robin_hood::unordered_map<IDEvent, std::vector<RE::SpellItem*>> keyTraceMap_EventID_Keyboard;
	static robin_hood::unordered_map<IDEvent, std::vector<RE::SpellItem*>> keyTraceMap_EventID_Mouse;
	static robin_hood::unordered_map<IDEvent, std::vector<RE::SpellItem*>> keyTraceMap_EventID_GamePad;
};
