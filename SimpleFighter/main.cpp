#include "SDL_MyWindow.hpp"
#include "Character.h"
#undef main
#include "SDL.h"

#include <iostream>

int main() {
	// Window object
	SDL_MyWindow window(640, 360, "SimpleFighter");

	bool end = false;			// Has the game ended jet?
	SDL_Event ev;				// Storing the event

	Character player;			// Player object

	while (!end) {
		// Getting event
		while (SDL_PollEvent(&ev)) {
			// If quit button pressed
			if (ev.type == SDL_QUIT)
				end = true;
			// If keyboard is pressed
			if (ev.type == SDL_KEYDOWN) {

				
				// Switching between the buttons, set the correct to true
				switch (ev.key.keysym.sym) {
				case SDLK_w:
					player.keys[0] = 1;
					break;
				case SDLK_a:
					player.keys[1] = 1;
					player.left = true;			// Direction (needed for jumping)
					break;
				case SDLK_s:
					player.keys[2] = 1;
					break;
				case SDLK_d:
					player.keys[3] = 1;
					player.left = false;			// Direction (needed for jumping)
					break;
				case SDLK_i:
					player.keys[4] = 1;
					player.jump();					// Jump the player
					break;
				case SDLK_j:
					player.keys[5] = 1;
					break;
				case SDLK_k:
					player.keys[6] = 1;
					break;
				case SDLK_l:
					player.keys[7] = 1;
					break;
				default:
					break;
				}
			}
			// If keyboard button is lifted, set that to false
			if (ev.type == SDL_KEYUP) {
				switch (ev.key.keysym.sym) {
				case SDLK_w:
					player.keys[0] = 0;
					break;
				case SDLK_a:
					player.keys[1] = 0;
					break;
				case SDLK_s:
					player.keys[2] = 0;
					break;
				case SDLK_d:
					player.keys[3] = 0;
					break;
				case SDLK_i:
					player.keys[4] = 0;
					break;
				case SDLK_j:
					player.keys[5] = 0;
					break;
				case SDLK_k:
					player.keys[6] = 0;
					break;
				case SDLK_l:
					player.keys[7] = 0;
					break;
				default:
					break;
				}
			}
		}

		// Clearing, updateing, redrawing the player character
		window.clearCharacter(player);
		player.update();
		window.drawCharacter(player);
		window.present();

		SDL_Delay(30);
	}

	return 0;
}