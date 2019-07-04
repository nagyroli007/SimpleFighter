#include "Character.h"

// Updating the vertical crouch strike animation  based on the frames
void Character::updateVrtCrouchStrike() {
	// If the strike direction is right, and the current sprite is one of them, then reset the timer, so it starts from the begining
	if (anim == VRTSTRIKECROUCH_R && (spritePhase < 34 || spritePhase > 36)) {
		animationTimer = 0;
	}
	else if (anim == VRTSTRIKECROUCH_L && (spritePhase < 64 || spritePhase > 66)) {
		animationTimer = 0;
	}

	// Switch between images every 4 frames
	switch (animationTimer / 4) {
	case 0:
		spritePhase = 36;
		inProgress = true;				// set inprogress true, so while this isn' finished, no new animation will start
		break;
	case 1:
		spritePhase = 35;
		break;
	case 2:
		spritePhase = 34;
		break;
	default:
		// End progress
		// Set animation timer to 110, so if in the crouching animation see 110 (+1), then it wont sart the crouching animation from the begining, because he player is already crouching
		if (anim == VRTSTRIKECROUCH_L)
			anim = CROUCH_L;
		else
			anim = CROUCH_R;
		inProgress = false;
		animationTimer = 110;
		break;
	}

	// If the player faces left, the switch to the left animations
	if (anim == VRTSTRIKECROUCH_L)
		spritePhase += 30;

	// Add to timer
	animationTimer++;
}

// Similar
void Character::updateVrtStrike() {
	if (anim == VRTSTRIKE_R && (spritePhase < 24 || spritePhase > 26)) {
		animationTimer = 0;
	}
	else if (anim == VRTSTRIKE_L && (spritePhase < 74 || spritePhase > 76)) {
		animationTimer = 0;
	}


	switch (animationTimer / 4) {
	case 0:
		spritePhase = 26;
		inProgress = true;
		break;
	case 1:
		spritePhase = 25;
		break;
	case 2:
		spritePhase = 24;
		break;
	default:
		if (anim == VRTSTRIKE_L)
			anim = STAND_L;
		else
			anim = STAND_R;
		inProgress = false;
		animationTimer = -1;
		break;
	}

	if (anim == VRTSTRIKE_L)
		spritePhase += 50;

	animationTimer++;
}

// Similar
void Character::updateHrzCrouchStrike() {
	if (anim == HRZSTRIKECROUCH_R && (spritePhase < 30 || spritePhase > 33)) {
		animationTimer = 0;
	}
	else if (anim == HRZSTRIKECROUCH_L && (spritePhase < 60 || spritePhase > 63)) {
		animationTimer = 0;
	}

	if (!up) {
		switch (animationTimer / 3) {
		case 0:
			spritePhase = 33;
			inProgress = true;
			break;
		case 1:
			spritePhase = 32;
			break;
		case 2:
			spritePhase = 31;
			break;
		case 3:
			spritePhase = 30;
			break;
		default:
			if (anim == HRZSTRIKECROUCH_L)
				anim = CROUCH_L;
			else
				anim = CROUCH_R;
			inProgress = false;
			animationTimer = 110;
			break;
		}
	}
	else {
		switch (animationTimer / 3) {
		case 0:
			spritePhase = 30;
			inProgress = true;
			break;
		case 1:
			spritePhase = 31;
			break;
		case 2:
			spritePhase = 32;
			break;
		case 3:
			spritePhase = 33;
			break;
		default:
			if (anim == HRZSTRIKECROUCH_L)
				anim = CROUCH_L;
			else
				anim = CROUCH_R;
			inProgress = false;
			animationTimer = 110;
			break;
		}
	}

	if (anim == HRZSTRIKECROUCH_L)
		spritePhase += 30;

	animationTimer++;
}

// Similar
void Character::updateHrzStrike() {
	if (anim == HRZSTRIKE_R && (spritePhase < 20 || spritePhase > 23)) {
		animationTimer = 0;
	}
	else if (anim == HRZSTRIKE_L && (spritePhase < 70 || spritePhase > 73)) {
		animationTimer = 0;
	}

	if (!up) {
		switch (animationTimer / 3) {
		case 0:
			spritePhase = 23;
			inProgress = true;
			break;
		case 1:
			spritePhase = 22;
			break;
		case 2:
			spritePhase = 21;
			break;
		case 3:
			spritePhase = 20;
			break;
		default:
			if (anim == HRZSTRIKE_L)
				anim = STAND_L;
			else
				anim = STAND_R;
			inProgress = false;
			animationTimer = -1;
			break;
		}
	}
	else {
		switch (animationTimer / 3) {
		case 0:
			spritePhase = 20;
			inProgress = true;
			break;
		case 1:
			spritePhase = 21;
			break;
		case 2:
			spritePhase = 22;
			break;
		case 3:
			spritePhase = 23;
			break;
		default:
			if (anim == HRZSTRIKE_L)
				anim = STAND_L;
			else
				anim = STAND_R;
			inProgress = false;
			animationTimer = -1;
			break;
		}
	}

	if (anim == HRZSTRIKE_L)
		spritePhase += 50;

	animationTimer++;
}

// Similar
void Character::updatePunchCrouchPhase() {
	if (anim == PUNCHCROUCH_R && (spritePhase < 37 || spritePhase > 38)) {
		animationTimer = 0;
	}
	else if (anim == PUNCHCROUCH_L && (spritePhase < 67 || spritePhase > 68)) {
		animationTimer = 0;
	}

	switch (animationTimer / 3) {
	case 0:
		spritePhase = 37;
		inProgress = true;
		break;
	case 1:
		spritePhase = 38;
		// CHECK HIT
		break;
	case 2:
		spritePhase = 37;
		break;
	default:
		if (anim == PUNCHCROUCH_L) {
			anim = CROUCH_L;
		}
		else {
			anim = CROUCH_R;
		}
		inProgress = false;
		animationTimer = 110;
		break;
	}

	if (anim == PUNCHCROUCH_L)
		spritePhase += 30;

	animationTimer++;
}

// Similar
void Character::updatePunchPhase() {
	if (anim == PUNCH_R && (spritePhase < 27 || spritePhase > 28)) {
		animationTimer = 0;
	}
	else if (anim == PUNCH_L && (spritePhase < 77 || spritePhase > 78)) {
		animationTimer = 0;
	}

	switch (animationTimer / 3) {
	case 0:
		spritePhase = 27;
		inProgress = true;
		break;
	case 1:
		spritePhase = 28;
		// CHECK HIT
		break;
	case 2:
		spritePhase = 27;
		break;
	default:
		if (anim == PUNCH_L) {
			anim = STAND_L;
		}
		else {
			anim = STAND_R;
		}
		inProgress = false;
		animationTimer = -1;
		break;
	}

	if (anim == PUNCH_L)
		spritePhase += 50;

	animationTimer++;
}

// Similar
void Character::updateCrouchPhase() {
	if (anim == CROUCH_R && (spritePhase < 7 || spritePhase > 9) && animationTimer != 111) {
		animationTimer = 0;
	}
	else if (anim == CROUCH_L && spritePhase < 97 && animationTimer != 111) {
		animationTimer = 0;
	}

	switch (animationTimer / 1) {
	case 0:
		spritePhase = 7;
		break;
	case 1:
		spritePhase = 8;
		break;
	default:
		spritePhase = 9;
		animationTimer--;
		break;
	}

	if (anim == CROUCH_L)
		spritePhase += 90;

	animationTimer++;
}

// If the player is walking, then this is calles
// Updates the sprite phase based on direction, and animation time
void Character::updateWalkPhase() {
	if (anim == WALK_R && (spritePhase < 1 || spritePhase > 6)) {
		animationTimer = 0;
	}
	else if (anim == WALK_L && (spritePhase < 91 || spritePhase > 96)) {
		animationTimer = 0;
	}

	switch (animationTimer / 4) {
	case 0:
		spritePhase = 5;
		break;
	case 1:
		spritePhase = 6;
		break;
	case 2:
		spritePhase = 1;
		break;
	case 3:
		spritePhase = 2;
		break;
	case 4:
		spritePhase = 3;
		break;
	case 5:
		spritePhase = 4;
		break;
	default:
		animationTimer = 0;
		break;
	}

	if (anim == WALK_L)
		spritePhase += 90;

	animationTimer++;
}