#include "movementInputTracer.h"
#include "settings.h"
#include "utils.h"
#include "hasher.hpp"
#include <math.h>      
#define PI 3.1415926535
const char* movementInputTraceSettingsDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\settings.ini";


void movementInputTracer::loadMovementTraceSpells() {
	INFO("loading movement trace spells...");
	CSimpleIniA pluginSettings;
	if (!utils::readSimpleIni(pluginSettings, movementInputTraceSettingsDir)) {
		return;
	}

	auto data = RE::TESDataHandler::GetSingleton();
	auto fwd = pluginSettings.GetValue("MovementInputTrace", "forwardMovementSpell");
	auto bwd = pluginSettings.GetValue("MovementInputTrace", "backwardMovementSpell");
	auto left = pluginSettings.GetValue("MovementInputTrace", "leftMovementSpell");
	auto right = pluginSettings.GetValue("MovementInputTrace", "rightMovementSpell");
	gameDataUilts::loadForm(data, movementSpell_forward, fwd);
	gameDataUilts::loadForm(data, movementSpell_back, bwd);
	gameDataUilts::loadForm(data, movementSpell_left, left);
	gameDataUilts::loadForm(data, movementSpell_right, right);
	INFO("...done");
}

void movementInputTracer::onForward(bool activate) {
	if (activate) {
		utils::addSpellToPlayer(movementSpell_forward);
		DEBUG("forward down");
	}
	else {
		utils::removeSpellFromPlayer(movementSpell_forward);
		DEBUG("forward up");
	}
}

void movementInputTracer::onBack(bool activate) {
	if (activate) {
		utils::addSpellToPlayer(movementSpell_back);
		DEBUG("back down");
	}
	else {
		utils::removeSpellFromPlayer(movementSpell_back);
		DEBUG("back up");
	}
}

void movementInputTracer::onLeft(bool activate) {
	if (activate) {
		utils::addSpellToPlayer(movementSpell_left);
		DEBUG("left down");
	}
	else {
		utils::removeSpellFromPlayer(movementSpell_left);
		DEBUG("left up");
	}
}

void movementInputTracer::onRight(bool activate) {
	if (activate) {
		DEBUG("right down");
		utils::addSpellToPlayer(movementSpell_right);
	}
	else {
		DEBUG("right up");
		utils::removeSpellFromPlayer(movementSpell_right);
	}
}
inline bool inRange(float num, double low, double high) {
	DEBUG("{}, {}, {}", num, low, high);
	return low < num && num <= high;
}

movementInputTracer::thumbStickZone movementInputTracer::getThumbStickZone(float x, float y) {
	
	float rad = atan2(y, x);
	if (rad < 0) {
		rad += 2 * PI;
	}
	DEBUG("getting thumstick zone for radian {}", rad);
	if (inRange(rad, 0, 1.0 / 8 * PI) || inRange(rad, 15.0 / 8 * PI, 0)) {
		DEBUG("R");
		return thumbStickZone::right;
	}
	else if (inRange(rad, 1.0 / 8 * PI, 3.0 / 8 * PI)) {
		DEBUG("UR");
		return thumbStickZone::upRight;
	}
	else if (inRange(rad, 3.0 / 8 * PI, 5.0 / 8 * PI)) {
		DEBUG("U");
		return thumbStickZone::up;
	}
	else if (inRange(rad, 5.0 / 8 * PI, 7.0 / 8 * PI)) {
		DEBUG("UL");
		return thumbStickZone::upLeft;
	}
	else if (inRange(rad, 7.0 / 8 * PI, 9.0 / 8 * PI)) {
		DEBUG("L");
		return thumbStickZone::left;
	}
	else if (inRange(rad, 9.0 / 8 * PI, 11.0 / 8 * PI)) {
		DEBUG("DL");
		return thumbStickZone::downLeft;
	}
	else if (inRange(rad, 11.0 / 8 * PI, 13.0 / 8 * PI)) {
		DEBUG("D");
		return thumbStickZone::down;
	}
	else if (inRange(rad, 13.0 / 8 * PI, 15.0 / 8 * PI)) {
		DEBUG("DR");
		return thumbStickZone::downRight;
	}
	
}

/*Process perfectly horizontal or vertical thumbstick movement.*/
void movementInputTracer::onPerfectThumbStickMovementInput(float x, float y) {
	DEBUG("perfect movement");
	if (x == 0) {
		if (prevThumbStickX > 0) {
			onRight(false);
		}
		else if (prevThumbStickX < 0) {
			onLeft(false);
		}
		if (y > 0) {
			if (prevThumbStickY < 0) {
				onForward(true);
				onBack(false);
			}
			else if (prevThumbStickY == 0) {
				onForward(true);
			}
			prevThumbStickZone = thumbStickZone::up;
		}
		else if (y < 0) {
			if (prevThumbStickY > 0) {
				onBack(true);
				onForward(false);
			}
			else if (prevThumbStickY == 0) {
				onBack(true);
			}
			prevThumbStickZone = thumbStickZone::down;
		}
		else {
			prevThumbStickZone = thumbStickZone::none;
		}
	}
	if (y == 0) {
		if (prevThumbStickY > 0) {
			onForward(false);
		}
		else if (prevThumbStickY < 0) {
			onBack(false);
		}
		if (x > 0) {
			if (prevThumbStickX < 0) {
				onRight(true);
				onLeft(false);
			}
			else if (prevThumbStickX == 0) {
				onRight(true);
			}
			prevThumbStickZone = thumbStickZone::right;
		}
		else if (x < 0) {
			if (prevThumbStickX > 0) {
				onLeft(true);
				onRight(false);
			}
			else if (prevThumbStickX == 0) {
				onLeft(true);
			}
			prevThumbStickZone = thumbStickZone::left;
		}
		else {
			prevThumbStickZone = thumbStickZone::none;
		}
	}
}
bool movementInputTracer::updateProximityThumbstickZone(thumbStickZone newThumbStickZone) {
	switch (newThumbStickZone) {
	case thumbStickZone::down:
		switch (prevThumbStickZone) {
		case thumbStickZone::down: return true;
		case thumbStickZone::downLeft: onLeft(false); return true;
		case thumbStickZone::downRight: onRight(false); return true;
		} 
	case thumbStickZone::up:
		switch (prevThumbStickZone) {
		case thumbStickZone::up: return true;
		case thumbStickZone::upLeft: onLeft(false); return true;
		case thumbStickZone::upRight: onRight(false); return true;
		}
	case thumbStickZone::left:
		switch (prevThumbStickZone) {
		case thumbStickZone::left: return true;
		case thumbStickZone::upLeft: onForward(false); return true;
		case thumbStickZone::downLeft: onBack(false); return true;
		}
	case thumbStickZone::right:
		switch (prevThumbStickZone) {
		case thumbStickZone::right: return true;
		case thumbStickZone::downRight: onBack(false); return true;
		case thumbStickZone::upRight: onForward(false); return true;
		}
	case thumbStickZone::upLeft:
		switch (prevThumbStickZone) {
		case thumbStickZone::upLeft: return true;
		case thumbStickZone::up: onLeft(true); return true;
		case thumbStickZone::left: onForward(true); return true;
		case thumbStickZone::upRight: onRight(false); onLeft(true); return true;
		case thumbStickZone::downLeft: onBack(false); onForward(true); return true;
		}
	case thumbStickZone::downLeft:
		switch (prevThumbStickZone) {
		case thumbStickZone::downLeft: return true;
		case thumbStickZone::down: onLeft(true); return true;
		case thumbStickZone::left: onBack(true); return true;
		case thumbStickZone::downRight: onRight(false); onLeft(true); return true;
		case thumbStickZone::upLeft: onForward(false); onBack(true); return true;
		}
	case thumbStickZone::upRight:
		switch (prevThumbStickZone) {
		case thumbStickZone::upRight: return true;
		case thumbStickZone::up: onRight(true); return true;
		case thumbStickZone::right: onForward(true); return true;
		case thumbStickZone::upLeft: onLeft(false); onRight(true); return true;
		case thumbStickZone::downRight: onBack(false); onForward(true); return true;
		}
	case thumbStickZone::downRight:
		switch (prevThumbStickZone) {
		case thumbStickZone::downRight: return true;
		case thumbStickZone::down: onRight(true); return true;
		case thumbStickZone::right: onBack(true); return true;
		case thumbStickZone::downLeft: onLeft(false); onRight(true); return true;
		case thumbStickZone::upRight: onForward(false); onBack(true); return true;
		}
	}

	return false;
}

void movementInputTracer::updateThumbstickInputTrace(thumbStickZone newThumbStickZone) {
	//DEBUG("inperfect movement, start tracing...");
	if (!updateProximityThumbstickZone(newThumbStickZone)) {
		switch (prevThumbStickZone) {
		case thumbStickZone::up: onForward(false); break;
		case thumbStickZone::down: onBack(false); break;
		case thumbStickZone::left: onLeft(false); break;
		case thumbStickZone::right: onRight(false); break;
		case thumbStickZone::upLeft: onForward(false); onLeft(false); break;
		case thumbStickZone::upRight: onForward(false); onRight(false); break;
		case thumbStickZone::downLeft: onBack(false); onLeft(false); break;
		case thumbStickZone::downRight: onBack(false); onRight(false); break;
		}
		switch (newThumbStickZone) {
		case thumbStickZone::up: onForward(true); break;
		case thumbStickZone::down: onBack(true); break;
		case thumbStickZone::left: onLeft(true); break;
		case thumbStickZone::right: onRight(true); break;
		case thumbStickZone::upLeft: onForward(true); onLeft(true); break;
		case thumbStickZone::upRight: onForward(true); onRight(true); break;
		case thumbStickZone::downLeft: onBack(true); onLeft(true); break;
		case thumbStickZone::downRight: onBack(true); onRight(true); break;
		}
	}
	prevThumbStickZone = newThumbStickZone;

}

void movementInputTracer::onThumbStickMovement(RE::ThumbstickEvent* a_thumbStickMovementInput) {
	auto x = a_thumbStickMovementInput->xValue;
	auto y = a_thumbStickMovementInput->yValue;
	DEBUG("x: {}, y: {}", x, y);
	updateThumbstickInputTrace(getThumbStickZone(x, y));
	prevThumbStickX = x;
	prevThumbStickY = y;
}

void movementInputTracer::onKeyBoardMovement(RE::ButtonEvent* a_keyboardMovementInput) {
	if (a_keyboardMovementInput->IsDown()) {
		auto userEvent = static_cast<std::string>(a_keyboardMovementInput->QUserEvent());
		switch (hash(userEvent)) {
		case "Forward"_h: onForward(); break;
		case "Back"_h: onBack(); break;
		case "Strafe Right"_h: onRight(); break;
		case "Strafe Left"_h: onLeft(); break;
		}
	}
	else if (a_keyboardMovementInput->IsUp()) {
		auto userEvent = static_cast<std::string>(a_keyboardMovementInput->QUserEvent());
		switch (hash(userEvent)) {
		case "Forward"_h: onForward(false); break;
		case "Back"_h: onBack(false); break;
		case "Strafe Right"_h: onRight(false); break;
		case "Strafe Left"_h: onLeft(false); break;
		}
	}
}