#pragma once
class movementInputTracer
{
public:
	enum thumbStickZone {
		none = 0,
		up,
		down,
		left,
		right,
		upLeft,
		upRight,
		downLeft,
		downRight
	};

	movementInputTracer() {
		prevThumbStickZone = thumbStickZone::none;
		prevThumbStickX = 0;
		prevThumbStickY = 0;

	}

	static movementInputTracer* GetSingleton()
	{
		static movementInputTracer singleton;
		return  std::addressof(singleton);
	}
	void loadMovementTraceSpells();
	inline void onPerfectThumbStickMovementInput(float x, float y);
	inline bool updateProximityThumbstickZone(thumbStickZone new_thumbStickZone);
	inline void updateThumbstickInputTrace(thumbStickZone new_thumbStickZone);
	inline thumbStickZone getThumbStickZone(float x, float y);
	void onThumbStickMovement(RE::ThumbstickEvent* a_thumbStickMovementInput);
	void onKeyBoardMovement(RE::ButtonEvent* a_keyboardMovementInput);
private:
	inline void onForward(bool activate = true);
	inline void onBack(bool activate = true);
	inline void onLeft(bool activate = true);
	inline void onRight(bool activate = true);
	thumbStickZone prevThumbStickZone;
	float prevThumbStickX;
	float prevThumbStickY;
	RE::SpellItem* movementSpell_forward;
	RE::SpellItem* movementSpell_back;
	RE::SpellItem* movementSpell_left;
	RE::SpellItem* movementSpell_right;
};