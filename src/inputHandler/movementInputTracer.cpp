#include "movementInputTracer.h"
#include "settings.h"
#include "utils.h"
#include "hasher.hpp"
#include <math.h>

#define PI 3.1415926535
const char* movementInputTraceSettingsDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\settings.ini";



void movementInputTracer::loadMovementTraceSpells() {
	logger::info("loading movement trace spells...");
	CSimpleIniA pluginSettings;
	if (!simpleIniUtils::readSimpleIni(pluginSettings, movementInputTraceSettingsDir)) {
		return;
	}
	auto data = RE::TESDataHandler::GetSingleton();
	auto fwd = pluginSettings.GetValue("MovementInputTrace", "spell_forward");
	auto bwd = pluginSettings.GetValue("MovementInputTrace", "spell_backward");
	auto left = pluginSettings.GetValue("MovementInputTrace", "spell_left");
	auto right = pluginSettings.GetValue("MovementInputTrace", "spell_right");
	auto TDM_Mgef = pluginSettings.GetValue("MovementInputTrace", "TDM_TargetLockMGEF");
	gameDataUilts::loadForm(data, movementSpell_forward, fwd);
	gameDataUilts::loadForm(data, movementSpell_back, bwd);
	gameDataUilts::loadForm(data, movementSpell_left, left);
	gameDataUilts::loadForm(data, movementSpell_right, right);
	if (settings::bTraceOnlyWhenTargetLock) {
		gameDataUilts::loadForm(data, TDM_TargetLockMGEF, TDM_Mgef);
	}
	logger::info("...done");
}

void movementInputTracer::onForward(bool activate) {
	if (activate) {
		if (settings::bTraceOnlyWhenTargetLock) {//check TDM's target lock
			auto pc = RE::PlayerCharacter::GetSingleton();
			if (!pc || !pc->AsMagicTarget()->HasMagicEffect(TDM_TargetLockMGEF)) {
				return;
			}
		}
		utils::addSpellToPlayer(movementSpell_forward);
	}
	else {
		utils::removeSpellFromPlayer(movementSpell_forward);
	}
}

void movementInputTracer::onBack(bool activate) {
	if (activate) {
		if (settings::bTraceOnlyWhenTargetLock) {//check TDM's target lock
			auto pc = RE::PlayerCharacter::GetSingleton();
			if (!pc || !pc->AsMagicTarget()->HasMagicEffect(TDM_TargetLockMGEF)) {
				return;
			}
		}
		utils::addSpellToPlayer(movementSpell_back);
	}
	else {
		utils::removeSpellFromPlayer(movementSpell_back);
	}
}

void movementInputTracer::onLeft(bool activate) {
	if (activate) {
		if (settings::bTraceOnlyWhenTargetLock) {//check TDM's target lock
			auto pc = RE::PlayerCharacter::GetSingleton();
			if (!pc || !pc->AsMagicTarget()->HasMagicEffect(TDM_TargetLockMGEF)) {
				return;
			}
		}
		utils::addSpellToPlayer(movementSpell_left);
	}
	else {
		utils::removeSpellFromPlayer(movementSpell_left);
	}
}

void movementInputTracer::onRight(bool activate) {
	if (activate) {
		if (settings::bTraceOnlyWhenTargetLock) {//check TDM's target lock
			auto pc = RE::PlayerCharacter::GetSingleton();
			if (!pc || !pc->AsMagicTarget()->HasMagicEffect(TDM_TargetLockMGEF)) {
				return;
			}
		}
		utils::addSpellToPlayer(movementSpell_right);
	}
	else {
		utils::removeSpellFromPlayer(movementSpell_right);
	}
}
inline bool inRange(float num, double low, double high) {
	//DEBUG("{}, {}, {}", num, low, high);
	return low < num && num <= high;
}

inline bool InPIRange(float rad, double low, double high) {
	return (low * PI) < rad 
		&& rad <= (high * PI);
}
movementInputTracer::thumbStickZone movementInputTracer::getThumbStickZone(float x, float y) {
	if (x == 0 && y == 0) {
		return thumbStickZone::neutral;
	}
	float rad = atan2(y, x);
	if (rad < 0) {
		rad += 2 * PI;
	}
	if (settings::bThumbStickOctodirecitonalTrace) {
		if (InPIRange(rad, 0, 1.0 / 8) || InPIRange(rad, 15.0 / 8, 2) || rad == 0) {
			return thumbStickZone::right;
		}
		else if (InPIRange(rad, 1.0 / 8, 3.0 / 8)) {
			return thumbStickZone::upRight;
		}
		else if (InPIRange(rad, 3.0 / 8, 5.0 / 8)) {
			return thumbStickZone::up;
		}
		else if (InPIRange(rad, 5.0 / 8, 7.0 / 8)) {
			return thumbStickZone::upLeft;
		}
		else if (InPIRange(rad, 7.0 / 8, 9.0 / 8)) {
			return thumbStickZone::left;
		}
		else if (InPIRange(rad, 9.0 / 8, 11.0 / 8)) {
			return thumbStickZone::downLeft;
		}
		else if (InPIRange(rad, 11.0 / 8, 13.0 / 8)) {
			return thumbStickZone::down;
		}
		else if (InPIRange(rad, 13.0 / 8, 15.0 / 8)) {
			return thumbStickZone::downRight;
		}
	}
	else {
		if (InPIRange(rad, 0, 1.0 / 4) || InPIRange(rad, 7.0 / 4, 2) || rad == 0) {
			return thumbStickZone::right;
		}
		else if (InPIRange(rad, 1.0 / 4, 3.0 / 4)) {
			return thumbStickZone::up;
		}
		else if (InPIRange(rad, 3.0 / 4, 5.0 / 4)) {
			return thumbStickZone::left;
		}
		else if (InPIRange(rad, 5.0 / 4, 7.0 / 4)) {
			return thumbStickZone::down;
		}

	}
	return thumbStickZone::neutral;
	
}

bool movementInputTracer::updateProximityThumbstickZone(thumbStickZone newThumbStickZone) {
	switch (newThumbStickZone) {
	case thumbStickZone::down:
		switch (prevThumbStickZone) {
		case thumbStickZone::down: return true;
		case thumbStickZone::downLeft: onLeft(false); return true;
		case thumbStickZone::downRight: onRight(false); return true;
		}
		break;
	case thumbStickZone::up:
		switch (prevThumbStickZone) {
		case thumbStickZone::up: return true;
		case thumbStickZone::upLeft: onLeft(false); return true;
		case thumbStickZone::upRight: onRight(false); return true;
		}
		break;
	case thumbStickZone::left:
		switch (prevThumbStickZone) {
		case thumbStickZone::left: return true;
		case thumbStickZone::upLeft: onForward(false); return true;
		case thumbStickZone::downLeft: onBack(false); return true;
		}
		break;
	case thumbStickZone::right:
		switch (prevThumbStickZone) {
		case thumbStickZone::right: return true;
		case thumbStickZone::downRight: onBack(false); return true;
		case thumbStickZone::upRight: onForward(false); return true;
		}
		break;
	case thumbStickZone::upLeft:
		switch (prevThumbStickZone) {
		case thumbStickZone::upLeft: return true;
		case thumbStickZone::up: onLeft(true); return true;
		case thumbStickZone::left: onForward(true); return true;
		case thumbStickZone::upRight: onRight(false); onLeft(true); return true;
		case thumbStickZone::downLeft: onBack(false); onForward(true); return true;
		}
		break;
	case thumbStickZone::downLeft:
		switch (prevThumbStickZone) {
		case thumbStickZone::downLeft: return true;
		case thumbStickZone::down: onLeft(true); return true;
		case thumbStickZone::left: onBack(true); return true;
		case thumbStickZone::downRight: onRight(false); onLeft(true); return true;
		case thumbStickZone::upLeft: onForward(false); onBack(true); return true;
		}
		break;
	case thumbStickZone::upRight:
		switch (prevThumbStickZone) {
		case thumbStickZone::upRight: return true;
		case thumbStickZone::up: onRight(true); return true;
		case thumbStickZone::right: onForward(true); return true;
		case thumbStickZone::upLeft: onLeft(false); onRight(true); return true;
		case thumbStickZone::downRight: onBack(false); onForward(true); return true;
		}
		break;
	case thumbStickZone::downRight:
		switch (prevThumbStickZone) {
		case thumbStickZone::downRight: return true;
		case thumbStickZone::down: onRight(true); return true;
		case thumbStickZone::right: onBack(true); return true;
		case thumbStickZone::downLeft: onLeft(false); onRight(true); return true;
		case thumbStickZone::upRight: onForward(false); onBack(true); return true;
		}
		break;
	}
	return false;
}


void movementInputTracer::updateThumbstickInputTrace(thumbStickZone newThumbStickZone) {
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
	//DEBUG("x: {}, y: {}", x, y);
	updateThumbstickInputTrace(getThumbStickZone(a_thumbStickMovementInput->xValue, a_thumbStickMovementInput->yValue));
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
