#pragma once
class movementInputTracer
{
public:
	enum movementDirection {
		none,
		forward,
		back,
		left,
		right
	};

	movementInputTracer() {
		thumbStickX = -99;
		thumbStickY = -99;
	}

	static movementInputTracer* GetSingleton()
	{
		static movementInputTracer singleton;
		return  std::addressof(singleton);
	}
	void loadMovementTraceSpells();

	void onThumbStickMovement(RE::ThumbstickEvent* a_thumbStickMovementInput);
	void onKeyBoardMovement(RE::ButtonEvent* a_keyboardMovementInput, movementDirection a_direction);
private:
	inline void onForward(bool activate = true);
	inline void onBack(bool activate = true);
	inline void onLeft(bool activate = true);
	inline void onRight(bool activate = true);
	float thumbStickX;
	float thumbStickY;



	RE::SpellItem* movementSpell_forward;
	RE::SpellItem* movementSpell_back;
	RE::SpellItem* movementSpell_left;
	RE::SpellItem* movementSpell_right;
};