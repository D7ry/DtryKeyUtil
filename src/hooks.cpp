#include "hooks.h"
#include "inputHandler/movementInputTracer.h"
namespace hooks
{
	void hook_movement::ProcessButton(RE::MovementHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data){
		movementInputTracer::GetSingleton()->onKeyBoardMovement(a_event);
		_ProcessButton(a_this, a_event, a_data);
	}

	void hook_movement::ProcessThumbstick(RE::MovementHandler* a_this, RE::ThumbstickEvent* a_event, RE::PlayerControlsData* a_data) {
		movementInputTracer::GetSingleton()->onThumbStickMovement(a_event);
		_ProcessThumbstick(a_this, a_event, a_data);
	}

	void install()
	{
		hook_movement::install();
	}
	
}
