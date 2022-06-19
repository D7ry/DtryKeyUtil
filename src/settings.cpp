#include "settings.h"
#include "utils.h"
const char* settingsDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\settings.ini";


void settings::ReadIntSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, uint32_t& a_setting) {
	const char* bFound = nullptr;
	bFound = a_ini.GetValue(a_sectionName, a_settingName);
	if (bFound) {
		//INFO("found {} with value {}", a_settingName, bFound);
		a_setting = static_cast<int>(a_ini.GetDoubleValue(a_sectionName, a_settingName));
	}
}
void settings::ReadFloatSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, float& a_setting)
{
	const char* bFound = nullptr;
	bFound = a_ini.GetValue(a_sectionName, a_settingName);
	if (bFound) {
		//INFO("found {} with value {}", a_settingName, bFound);
		a_setting = static_cast<float>(a_ini.GetDoubleValue(a_sectionName, a_settingName));
	}
}

void settings::ReadBoolSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, bool& a_setting)
{
	const char* bFound = nullptr;
	bFound = a_ini.GetValue(a_sectionName, a_settingName);
	if (bFound)
	{
		//INFO("found {} with value {}", a_settingName, bFound);
		a_setting = a_ini.GetBoolValue(a_sectionName, a_settingName);
	}
}



void settings::readSettings() {
	readPluginSettings();
	readCustomConfigs();
}

void settings::readPluginSettings() {
	INFO("Reading plugin settings...");
	CSimpleIniA pluginSettings;
	if (!simpleIniUtils::readSimpleIni(pluginSettings, settingsDir)) {
		return;
	}

	ReadBoolSetting(pluginSettings, "General", "bLogUserEvent", bLogUserEvent);
	ReadBoolSetting(pluginSettings, "General", "bToggleMovementInputTrace", bToggleMovementInputTrace);
	ReadBoolSetting(pluginSettings, "General", "bToggleUserEventInputTrace", bToggleUserEventInputTrace); 
	ReadBoolSetting(pluginSettings, "General", "bToggleEventIDInputTrace", bToggleEventIDInputTrace);
	ReadBoolSetting(pluginSettings, "MovementInputTrace", "bTraceOnlyWhenTargetLock", bTraceOnlyWhenTargetLock);
	ReadBoolSetting(pluginSettings, "MovementInputTrace", "bThumbStickOctodirecitonalTrace", bThumbStickOctodirecitonalTrace);
	INFO("...done");
}

void settings::readCustomConfigs() {

}
