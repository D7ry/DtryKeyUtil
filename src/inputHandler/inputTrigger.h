#pragma once
class inputTrigger
{
public:
	enum triggerType {
		onKeyDown = 0,
		onKeyUp,
		onKeyHeld
	};

	inputTrigger(int a_keyCode, std::string a_userEvent) {
		
	}

	inputTrigger(int a_keyCode) {
		_keyCode = a_keyCode;
	}


	inputTrigger(std::string a_userEvent) {
		_userEvent = a_userEvent;
	}


	/*The input has been triggered.*/
	void trigger() {
		
	}
private:
	int _keyCode; //keycode that triggers this input callback
	std::string _userEvent; //userEvent that triggers this input callback
	RE::SpellItem* spellToCast;
	RE::BGSPerk* perkToAdd;

};
