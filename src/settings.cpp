#include "settings.h"

const char* settingsDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\settings.ini";
const char* movementInputTraceSettingsDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\movementInputTrace.ini";


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

bool settings::readSimpleIni(CSimpleIniA& a_ini, const char* a_iniAddress) {
	if (std::filesystem::exists(a_iniAddress)) {
		a_ini.LoadFile(a_iniAddress);
		return true;
	}
	else {
		ERROR("Error: {} is not a valid .ini address.", a_iniAddress);
		return false;
	}

}


void settings::readSettings() {
	readPluginSettings();
	readCustomConfigs();
}

void settings::readPluginSettings() {
	INFO("Reading plugin settings...");
	CSimpleIniA pluginSettings;
	if (!readSimpleIni(pluginSettings, settingsDir)) {
		return;
	}

	ReadBoolSetting(pluginSettings, "General", "bLogUserEvent", bLogUserEvent);
	INFO("...done");
}

void settings::readCustomConfigs() {

}

void settings::readMovementKeyTraceConfig() {
	INFO("Reading movement key trace config...");
	CSimpleIniA movementKeyTraceConfig;
	if (!readSimpleIni(movementKeyTraceConfig, settingsDir)) {
		return;
	}


	INFO("...done");
}