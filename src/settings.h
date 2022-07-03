#pragma once
#include "lib/SimpleIni.h"

class settings
{
public:
	
	static void readSettings();
	static inline bool bLogUserEvent = false;
	static inline bool bToggleAnimEventTrigger = true;
	static inline bool bToggleMovementInputTrace = true;
	static inline bool bToggleUserEventInputTrace = true;
	static inline bool bToggleEventIDInputTrace = true;
	static inline bool bTraceOnlyWhenTargetLock = true;
	static inline bool bThumbStickOctodirecitonalTrace = true;
	using userInputEvent = std::string;
	using animationEvent = std::string;


	using buttonEvent = std::string;

private:
	static void readPluginSettings();
	static void readCustomConfigs();

	static void ReadBoolSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, bool& a_setting);
	static void ReadFloatSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, float& a_setting);
	static void ReadIntSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, uint32_t& a_setting);

};
