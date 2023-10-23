#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return EXIT_FAILURE;
	}
	SDL_Window* window = SDL_CreateWindow("SDL Tutorial", 400, 400, SDL_WINDOW_OPENGL);
	if (!window) {
		return EXIT_FAILURE;
	}
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	if (!surface) {
		return EXIT_FAILURE;
	}
	SDL_FillSurfaceRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}