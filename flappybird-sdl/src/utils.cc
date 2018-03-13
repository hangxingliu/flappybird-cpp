#include <stdio.h>
#include <SDL.h>

#include "./utils.h"

bool hasCollision(int x, int y, double r, int x0, int y0) {
	if(x + r < x0 - 25 || x - r > x0 + 25) return false;
	if(y - y0 < r || y0 + 150 - y < r)return true;
	return false;
}

void SDL_fatal(const char* forWhat) {
	fprintf(stderr, "fatal: (SDL) %s: %s\n", forWhat, SDL_GetError());
	exit(1);
}
