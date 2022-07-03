#pragma once
#include "settings.h"
#include "PCH.h"
#include "lib/robin_hood.h"
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

private:
	using animEventMap = std::unordered_map<IDEvent, std::vector<RE::BSFixedString>*>;
	inline void processAnimEventKey(animEventMap a_animEventMap, IDEvent a_event);
	static animEventMap animEventMap_EventID_Keyboard;
	static animEventMap animEventMap_EventID_Mouse;
	static animEventMap animEventMap_EventID_GamePad;

	inline void processAnimBoolFlipKey(animEventMap a_animEventMap, IDEvent a_event);
	static animEventMap animBoolMap_EventID_Keyboard;
	static animEventMap animBoolMap_EventID_Mouse;
	static animEventMap animBoolMap_EventID_GamePad;

};
