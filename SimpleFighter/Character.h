#pragma once

typedef enum phase { IDLE_L, IDLE_R, WALK_L, WALK_R, CROUCH_L, CROUCH_R,
					STANDUP_L, STANDUP_R, STAND_L, STAND_R, DMGHIGH_L, DMGHIGH_R,
					DMGLOW_L, DMGLOW_R, DMGCROUCH_L, DMGCROUCH_R, JUMP_L, JUMP_R,
					VRTSTRIKE_L, VRTSTRIKE_R, VRTSTRIKECROUCH_L, VRTSTRIKECROUCH_R,
					VRTSTRIKEJUMP_L, VRTSTRIKEJUMP_R, HRZSTRIKE_L, HRZSTRIKE_R,
					HRZSTRIKECROUCH_L, HRZSTRIKECROUCH_R, HRZSTRIKEJUMP_L,
					HRZSTRIKEJUMP_R, PUNCH_L, PUNCH_R, PUNCHCROUCH_L, PUNCHCROUCH_R,
					PUNCHJUMP_L, PUNCHJUMP_R, GUARD_L, GUARD_R, GUARDCROUCH_L,
					GUARDCROUCH_R, GUARDJUMP_L, GUARDJUMP_R, INAIR
};

#include <iostream>

class Character
{
	int spriteX, spriteY;				// Positions of the sprite top left corner
	int spriteWidth, spriteHeight;		// Dimension of a sprite
	int spritePhase;					// Which sprite needs to be loaded
	int speedX = 0, speedY = 0;			// Speed of the character
	int animationTimer = 0;				// Counts the  frames for animation, so i can switch sprite in time

	int walkSpeed = 3;

	phase anim = IDLE_L;
	bool inProgress = false;

public:
	bool left = false, up = false;		// Left for the direction while in air, up for the horizontal strike direction

	bool keys[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };		// Which keys are pressed down, are which aren't 

	// Constructor, sets position, dimensions
	Character() {
		spriteX = 100; spriteY = 296;
		spriteWidth = 32; spriteHeight = 64;
		spritePhase = 0;
	}

	// Getter functions
	int getSX() { return spriteX; }
	int getSY() { return spriteY; }
	int getSW() { return spriteWidth; }
	int getSH() { return spriteHeight; }
	int getSP() { return spritePhase; }

	//  Updating the character position, sprite phase, animation
	void update() {
		// If a moving key is pressed, and the player doesn' want to puch, strike or crouch
		// Then set the vertical speed
		if ((keys[1] || keys[3]) && !(keys[5] || keys[6] || keys[7]) && !inProgress) {
			if (keys[1]) {
				speedX = -walkSpeed;
				anim = WALK_L;
			}
			else {
				speedX = walkSpeed;
				anim = WALK_R;
			}
		}
		// If not moving, set speedX to 0
		else {
			// Set speedX 0, cause the player doesn't pres the left, right
			speedX = 0;
			// If doesn't doiang anything, then set to standing
			if (!(keys[4] || keys[5] || keys[6] || keys[7]) && !inProgress) {
				if (anim != STAND_L && anim != STAND_R)
					anim = (anim % 2 == 0) ? STAND_L : STAND_R;
			}
			
		}

		// Getting the new animation type, and updating the animation
		getAnimPhase();
		callAnimationUpdate();

		// If in the air, then add gravity to its horizontal speel
		if (!onGround()) {
			speedY = (speedY > 10) ? 10 : speedY + 1;
		}
		// If on the ground and doesn't want to jump again, then set speedY to 0
		else if (!keys[4])
			speedY = 0;

		// Updating the position
		spriteY += speedY;
		spriteX += speedX;
	}

	// Returns, if the player is on the ground level
	// If he is under the bottom pixel, then set the position, so he is on the bottom
	bool onGround() {
		if (spriteY == 296)
			return true;
		else if (spriteY > 296) {
			spriteY = 296;
			return true;
		}
		return false;
	}

	// Jump, gives -Y speed to the character, is it will start going up 
	void jump() {
		if (onGround() && !keys[6])
			speedY = -10;
	}

private:
	// Updating the animation type, based on Y position, keys pressed
	void getAnimPhase() {
		// If in air, set jumping sprite
		if (!onGround()) {
			anim = INAIR;
			spritePhase = 17;
			if (left)
				spritePhase += 70;
		}
		// Horizontal standing strike
		else if (keys[5] && !keys[6] && !inProgress && (keys[0] || keys[2])) {
			// If the animation is not already horizontal standing strike, then set it to that
			if (anim != HRZSTRIKE_L && anim != HRZSTRIKE_R)
				anim = (anim % 2 == 0) ? HRZSTRIKE_L : HRZSTRIKE_R;
			// Storing if the hand should go up or down (invert of the up key)
			up = !keys[0];
		}
		// Horizontal crouching strike
		else if (keys[5] && keys[6] && !inProgress && (keys[0] || keys[2])) {
			if (anim != HRZSTRIKECROUCH_L && anim != HRZSTRIKECROUCH_R) {
				anim = (anim % 2 == 0) ? HRZSTRIKECROUCH_L : HRZSTRIKECROUCH_R;
				animationTimer = 0;
			}
			up = !keys[0];
		}
		// Vertical standing strike
		else if (keys[5] && !keys[6] && !inProgress && (keys[1] || keys[3])) {
			if (anim != VRTSTRIKEJUMP_L && anim != VRTSTRIKE_R)
				anim = (keys[1]) ? VRTSTRIKE_L : VRTSTRIKE_R;
		}
		// Vertical crouching strike
		else if (keys[5] && keys[6] && !inProgress && (keys[1] || keys[3])) {
			if (anim != VRTSTRIKECROUCH_L && anim != VRTSTRIKECROUCH_R) {
				anim = (keys[1]) ? VRTSTRIKECROUCH_L : VRTSTRIKECROUCH_R;
				animationTimer = 0;
			}
		}
		// Standing basic punch
		else if (keys[5] && !keys[6] && !inProgress) {
			if (anim != PUNCH_L && anim != PUNCH_R) {
				anim = (anim % 2 == 0) ? PUNCH_L : PUNCH_R;
			}
		}
		// If crouching
		else if (keys[6]) {
			// Crouch basic punch
			if (keys[5] && !inProgress) {
				if (anim != PUNCHCROUCH_L && anim != PUNCHCROUCH_R) {
					anim = (anim % 2 == 0) ? PUNCHCROUCH_L : PUNCHCROUCH_R;
					animationTimer = 0;
				}
			}
			// If no punch, strike is in progress, then just crouch 
			else if (!inProgress) {
				if (anim != CROUCH_L && anim != CROUCH_R) {
					anim = (anim % 2 == 0) ? CROUCH_L : CROUCH_R;
				}
			}
		}
	}

	// Calls the corriect animation update funcion based on the animation type
	void callAnimationUpdate() {
		switch (anim) {
		case STAND_L:
			spritePhase = 90;
			break;
		case STAND_R:
			spritePhase = 0;
			break;
		case WALK_L:
			updateWalkPhase();
			break;
		case WALK_R:
			updateWalkPhase();
			break;
		case PUNCH_L:
			updatePunchPhase();
			break;
		case PUNCH_R:
			updatePunchPhase();
			break;
		case CROUCH_L:
			updateCrouchPhase();
			break;
		case CROUCH_R:
			updateCrouchPhase();
			break;
		case PUNCHCROUCH_L:
			updatePunchCrouchPhase();
			break;
		case PUNCHCROUCH_R:
			updatePunchCrouchPhase();
			break;
		case HRZSTRIKE_L:
			updateHrzStrike();
			break;
		case HRZSTRIKE_R:
			updateHrzStrike();
			break;
		case HRZSTRIKECROUCH_L:
			updateHrzCrouchStrike();
			break;
		case HRZSTRIKECROUCH_R:
			updateHrzCrouchStrike();
			break;
		case VRTSTRIKE_L:
			updateVrtStrike();
			break;
		case VRTSTRIKE_R:
			updateVrtStrike();
			break;
		case VRTSTRIKECROUCH_L:
			updateVrtCrouchStrike();
			break;
		case VRTSTRIKECROUCH_R:
			updateVrtCrouchStrike();
			break;
		}
	}

	// Updating the vertical crouch strike animation  based on the frames
	void updateVrtCrouchStrike();

	// Similar
	void updateVrtStrike();

	// Similar
	void updateHrzCrouchStrike();

	// Similar
	void updateHrzStrike();

	// Similar
	void updatePunchCrouchPhase();

	// Similar
	void updatePunchPhase();

	// Similar
	void updateCrouchPhase();

	// If the player is walking, then this is calles
	// Updates the sprite phase based on direction, and animation time
	void updateWalkPhase();
};

