#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

const char *path = "C:/Users/0/AppData/Roaming/pico-8/carts/tool-test-cart.p8";

int main (int argc, char **argv) {
	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_Window *w = SDL_CreateWindow (
		"hi",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280 * 0.75, 720 * 0.75,
		SDL_WINDOW_RESIZABLE);

	SDL_RWops *rw = SDL_RWFromFile (path, "r");
	if (rw == NULL) SDL_Log ("that aint right...");

	Uint8 buf[512];
	SDL_RWread (rw, buf, 1, 512);
	buf[511] = '\0';
	SDL_Log (buf);

	while (1) {
		SDL_Event e;
		while (SDL_PollEvent (&e))
			if (e.type == SDL_QUIT)
				goto endloop;
	}
	endloop:
	return 0;
}
