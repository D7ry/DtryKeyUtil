#pragma once
#include "lib/robin_hood.h"
#include "lib/SimpleIni.h"

class settings
{
public:
	
	static void readSettings();
	static inline bool bLogUserEvent = false;
	static inline bool bToggleMovementInputTrace = true;
	static inline bool bToggleUserEventInputTrace = true;
	static inline bool bToggleEventIDInputTrace = true;
	static inline bool bTraceOnlyWhenTargetLock = true;
	static inline bool bThumbStickOctodirecitonalTrace = true;
	using userInputEvent = std::string;
	using animationEvent = std::string;
	static inline robin_hood::unordered_set<userInputEvent> registeredEvents;

	static inline robin_hood::unordered_map<userInputEvent, animationEvent> animEventMap_u;
	static inline robin_hood::unordered_map<userInputEvent, std::vector<RE::SpellItem*>*> spellCastingMap_u;

	using buttonEvent = std::string;
	static inline robin_hood::unordered_map<buttonEvent, animationEvent> animEventMap_b;
	static inline robin_hood::unordered_map<buttonEvent, std::vector<RE::SpellItem*>*> keyTraceMap_b;
	static inline robin_hood::unordered_map<buttonEvent, std::vector<RE::SpellItem*>*> spellCastingMap_b;
private:
	static void readPluginSettings();
	static void readCustomConfigs();

	static void ReadBoolSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, bool& a_setting);
	static void ReadFloatSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, float& a_setting);
	static void ReadIntSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, uint32_t& a_setting);

};