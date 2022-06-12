#pragma once
#pragma once
#include "lib/robin_hood.h"
#include "lib/SimpleIni.h"
class inputTracer
{
public:
	using userInputEvent = std::string;

	static inputTracer* GetSingleton() {
		static inputTracer singleton;
		return  std::addressof(singleton);
	}

	void processUserInputTrace(userInputEvent a_userInput, bool isButtonDown);

	void loadInputTraceConfigs();
private:
	
	void loadInputTraceConfig(const char* a_iniPath);
	void loadUserInputConfig(CSimpleIniA& a_ini);
	static inline robin_hood::unordered_map<userInputEvent, std::vector<RE::SpellItem*>> keyTraceMap_u;
};