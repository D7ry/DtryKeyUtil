#pragma once
namespace hooks
{
	class hook_movement
	{
	public:
		static void install()
		{

			REL::Relocation<std::uintptr_t> MovementHandlerVtbl{ RE::VTABLE_MovementHandler[0] };

			//REL::Relocation<std::uintptr_t> MovementHandlerVtbl{ REL::ID(263056) };
			
			_ProcessThumbstick = MovementHandlerVtbl.write_vfunc(0x2, ProcessThumbstick);
			_ProcessButton = MovementHandlerVtbl.write_vfunc(0x4, ProcessButton);
		}

	private:
		static void ProcessThumbstick(RE::MovementHandler* a_this, RE::ThumbstickEvent* a_event, RE::PlayerControlsData* a_data);
		static void ProcessButton(RE::MovementHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data);

		static inline REL::Relocation<decltype(ProcessThumbstick)> _ProcessThumbstick;
		static inline REL::Relocation<decltype(ProcessButton)> _ProcessButton;
	};

	void install();
}
