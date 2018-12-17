#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <stdio.h>

/*
 This is all pretty rough right, now I'll error proof and
 clean it up once the basic sprite editor functionality
 is completed.
*/

typedef Uint8 u8;
typedef Uint32 u32;

u32 pal[] = {
	0x000000, 0x1d2b53, 0x7e2553, 0x008751,
	0xab5236, 0x5f574f, 0xc2c3c7, 0xfff1c8,
	0xff004d, 0xffa300, 0xffec27, 0x00e436,
	0x29adff, 0x83769c, 0xff77a8, 0xffccaa
};

const char *path = "C:/Users/0/AppData/Roaming/pico-8/carts/tool-test-cart.p8";

u8 pixels[128 * 128] = { 0 };

int pixel_scale = 3;

void load_pixels (SDL_RWops *rw) {
	u8 *str = "__gfx__";
	int si = 0;
	u8 r = 0;
	int p = 0;

	for (; SDL_RWread (rw, &r, 1, 1);) {
		if (str[si] == r) {
			si++;
		}
		else {
			if (str[si] == '\0')
				goto load;
			si = 0;
		}
	}

	return;

	load:
	for (; p < sizeof (pixels) && SDL_RWread (rw, &r, 1, 1);) {
		u8 pp = 0;

		if ((r < 'a' || r > 'f') && (r < '0' || r > '9'))
			continue;

		if (r >= 'a' && r <= 'f') pp = 10 + (r - 'a');
		if (r >= '0' && r <= '9') pp = r - '0';

		pixels[p] = pp;

		p++;
	}
}

int main (int argc, char **argv) {
	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_Window *w = SDL_CreateWindow (
		"hi",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280 * 0.75, 720 * 0.75,
		SDL_WINDOW_RESIZABLE);
	SDL_Renderer *r = SDL_CreateRenderer (w, -1, 0);

	SDL_RWops *rw = SDL_RWFromFile (path, "r");
	if (rw == NULL) SDL_Log ("that aint right...");

	load_pixels (rw);

	while (1) {
		SDL_Event e;
		while (SDL_PollEvent (&e))
			if (e.type == SDL_QUIT)
				goto endloop;

		static int iii = 0;
		iii++;
		if (iii == 16) iii = 0;
		unsigned int ii = pal[iii];
		SDL_SetRenderDrawColor (r, 0, 0, 0, 255);
		SDL_RenderClear (r);

		SDL_Rect rc = { 10, 10, 20, 20 };
		SDL_SetRenderDrawColor (r, ii >> 16 & 255, ii >> 8 & 255, ii & 255, 255);

		SDL_RenderSetScale (r, iii, iii);
		SDL_RenderFillRect (r, &rc);

		int c = pal[8];
		SDL_RenderSetScale (r, 3, 3);
		for (int x = 0; x < 128; x++)
			for (int y = 0; y < 128; y++) {
				c = pal[pixels[x + y * 128]];
				SDL_SetRenderDrawColor (r, c >> 16 & 255, c >> 8 & 255, c & 255, 255);
				SDL_RenderDrawPoint (r, x, y);
			}
		SDL_Delay (210);
		SDL_RenderPresent (r);
	}
	endloop:
	return 0;
}
