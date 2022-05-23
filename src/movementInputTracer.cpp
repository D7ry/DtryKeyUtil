#include "movementInputTracer.h"
#include "settings.h"
#include "utils.h"
const char* movementInputTraceSettingsDir = "Data\\SKSE\\Plugins\\dtryKeyUtil\\config\\settings.ini";


void movementInputTracer::loadMovementTraceSpells() {
	INFO("loading movement trace spells...");
	CSimpleIniA pluginSettings;
	if (!utils::readSimpleIni(pluginSettings, movementInputTraceSettingsDir)) {
		return;
	}

	auto data = RE::TESDataHandler::GetSingleton();
	auto fwd = pluginSettings.GetValue("MovementInputTrace", "forwardMovementSpell"); auto fwd_v = utils::tokenize(fwd, '|');
	auto bwd = pluginSettings.GetValue("MovementInputTrace", "backwardMovementSpell"); auto bwd_v = utils::tokenize(bwd, '|');
	auto left = pluginSettings.GetValue("MovementInputTrace", "leftMovementSpell"); auto left_v = utils::tokenize(left, '|');
	auto right = pluginSettings.GetValue("MovementInputTrace", "rightMovementSpell"); auto right_v = utils::tokenize(right, '|');
	utils::gameDataLoader::loadSpellItem(movementSpell_forward, *data, fwd_v[0], fwd_v[1]);
	utils::gameDataLoader::loadSpellItem(movementSpell_back, *data, bwd_v[0], bwd_v[1]);
	utils::gameDataLoader::loadSpellItem(movementSpell_left, *data, left_v[0], left_v[1]);
	utils::gameDataLoader::loadSpellItem(movementSpell_right, *data, right_v[0], right_v[1]);
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



void movementInputTracer::onThumbStickMovement(RE::ThumbstickEvent* a_thumbStickMovementInput) {
	auto x = a_thumbStickMovementInput->xValue;
	auto y = a_thumbStickMovementInput->yValue;
	DEBUG("{}, {}", x, y);

	if (x > 0) {
		if (prevThumbStickX <= 0) {
			onRight();
			if (prevThumbStickX < 0) {
				onLeft(false);
			}
		}
	}
	else if (x < 0) {
		if (prevThumbStickX >= 0) {
			onLeft();
			if (prevThumbStickX > 0) {
				onRight(false);
			}
		}
	}
	else { //x == 0
		if (prevThumbStickX < 0) {
			onLeft(false);
		}
		else if (prevThumbStickX > 0) {
			onRight(false);
		}
	}


	if (y > 0) {
		if (prevThumbStickY <= 0) {
			onForward();
			if (prevThumbStickY < 0) {
				onBack(false);
			}
		}
	}
	else if (y < 0) {
		if (prevThumbStickY >= 0) {
			onBack();
			if (prevThumbStickY > 0) {
				onForward(false);
			}
		}
	}
	else { //y == 0
		if (prevThumbStickY < 0) {
			onBack(false);
		}
		else if (prevThumbStickY > 0) {
			onForward(false);
		}
	}
	prevThumbStickX = x;
	prevThumbStickY = y;

}

void movementInputTracer::onKeyBoardMovement(RE::ButtonEvent* a_keyboardMovementInput, movementDirection a_direction) {
	if (a_keyboardMovementInput->IsDown()) {
		switch (a_direction) {
		case movementDirection::forward: onForward(); break;
		case movementDirection::back: onBack(); break;
		case movementDirection::left: onLeft(); break;
		case movementDirection::right: onRight(); break;
		}
	}
	else if (a_keyboardMovementInput->IsUp()) {
		switch (a_direction) {
		case movementDirection::forward: onForward(false); break;
		case movementDirection::back: onBack(false); break;
		case movementDirection::left: onLeft(false); break;
		case movementDirection::right: onRight(false); break;
		}
	}
}