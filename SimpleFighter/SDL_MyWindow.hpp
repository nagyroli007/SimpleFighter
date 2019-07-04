#include "SDL.h"
#include "SDL_image.h"
#include "Character.h"


class SDL_MyWindow {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height;

	SDL_Texture* playerTexture = NULL;

public:
	// Initializing necessary things
	SDL_MyWindow(int w = 600, int h = 400, const char* title = "title") : width(w), height(h) {
		SDL_Init(SDL_INIT_EVERYTHING);

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		playerTexture = IMG_LoadTexture(renderer, "frameGuide.png");

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	// Destroying the created things
	~SDL_MyWindow() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	// Clearing the sceen
	void clear() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
	}

	// Presenting the renderer
	void present() {
		SDL_RenderPresent(renderer);
	}

	// Drawing the character from its position and sprite phase
	void drawCharacter(Character& ch) {
		SDL_Rect d; d.x = ch.getSX(); d.y = ch.getSY(); d.w = ch.getSW(); d.h = ch.getSH();
		SDL_Rect s; s.x = ch.getSP() % 10 * 32; s.y = ch.getSP() / 10 * 64; s.w = 32; s.h = 64;
		//SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, playerTexture, &s, &d);
	}

	// Just clearing the player rectangle with white rectangle
	void clearCharacter(Character& ch) {
		SDL_Rect r; r.x = ch.getSX(); r.y = ch.getSY(); r.w = ch.getSW(); r.h = ch.getSH();
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &r);
	}
};