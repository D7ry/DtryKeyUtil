#pragma once
#include "settings.h"
class animEvent
{
public:
	static animEvent* GetSingleton()
	{
		static animEvent singleton;
		return std::addressof(singleton);
	}
	using IDEvent = uint32_t;

	void loadConfigs();

	void processInput(IDEvent a_eventID, RE::INPUT_DEVICE a_device);

	
	void loadIDAnimEventConfig_Mouse(CSimpleIniA& a_ini);
	void loadIDAnimEventConfig_Keyboard(CSimpleIniA& a_ini);
	void loadIDAnimEventConfig_GamePad(CSimpleIniA& a_ini);
	
	void loadIDAnimBoolConfig_Mouse(CSimpleIniA& a_ini);
	void loadIDAnimBoolConfig_Keyboard(CSimpleIniA& a_ini);
	void loadIDAnimBoolConfig_GamePad(CSimpleIniA& a_ini);


private:
	using animEventMap = std::unordered_map<IDEvent, std::shared_ptr<std::vector<RE::BSFixedString>>>;
	inline void processAnimEventKey(animEventMap a_animEventMap, IDEvent a_event);
	animEventMap animEventMap_EventID_Keyboard;
	animEventMap animEventMap_EventID_Mouse;
	animEventMap animEventMap_EventID_GamePad;

	inline void processAnimBoolFlipKey(animEventMap a_animEventMap, IDEvent a_event);
	animEventMap animBoolMap_EventID_Keyboard;
	animEventMap animBoolMap_EventID_Mouse;
	animEventMap animBoolMap_EventID_GamePad;

};
