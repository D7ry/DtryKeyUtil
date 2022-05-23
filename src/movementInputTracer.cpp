#include "movementInputTracer.h"
#include "hasher.hpp"

void movementInputTracer::loadMovementTraceSpells() {
	
}
void movementInputTracer::onForward(bool activate) {
	if (activate) {
		DEBUG("forward down");
	}
	else {
		DEBUG("forward up");
	}
}

void movementInputTracer::onBack(bool activate) {
	if (activate) {
		DEBUG("back down");
	}
	else {
		DEBUG("back up");
	}
}

void movementInputTracer::onLeft(bool activate) {
	if (activate) {
		DEBUG("left down");
	}
	else {
		DEBUG("left up");
	}
}

void movementInputTracer::onRight(bool activate) {
	if (activate) {
		DEBUG("right down");
	}
	else {
		DEBUG("right up");
	}
}



void movementInputTracer::onThumbStickMovement(RE::ThumbstickEvent* a_thumbStickMovementInput) {
	auto x = a_thumbStickMovementInput->xValue;
	auto y = a_thumbStickMovementInput->yValue;
	DEBUG("{}, {}", x, y);

	if (x == 0) {
		onRight(false);
		onLeft(false);
	}
	if (y == 0) {
		onForward(false);
		onBack(false);
	}
	if (x > 0) {
		if (thumbStickX <= 0) {
			onForward();
			if (thumbStickX < 0) {
				onBack(false);
			}
		}
	}
	else if (x < 0) {
		if (thumbStickX >= 0) {
			onBack();
			if (thumbStickX > 0) {
				onForward(false);
			}
		}
	}
	if (y > 0) {
		if (thumbStickY <= 0) {
			onLeft();
			if (thumbStickY < 0) {
				onRight(false);
			}
		}
	}
	else if (y < 0) {
		if (thumbStickY >= 0) {
			onRight();
			if (thumbStickY > 0) {
				onLeft(false);
			}
		}
	}
	thumbStickX = x;
	thumbStickY = y;

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