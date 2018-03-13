#include <SDL.h>
#include <SDL_image.h>

#include "./ui.h"

#ifndef BASE_IMAGE_HEADER
#define BASE_IMAGE_HEADER

class Image {
	private:
		SDL_Texture* texture;
		SDL_Surface* surface;
	public:
		SDL_Rect rect;
		Image(const char* fileName) {
			surface = IMG_Load(fileName);
			texture = SDL_CreateTextureFromSurface(ui::Render,surface);
			rect.x = rect.y = 0;
			rect.w = surface->w;
			rect.h = surface->h;
		}
		~Image() {
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
		void draw(int x,int y,int angle = 0) {
			SDL_Rect r;
			r.x = x; r.y = y; r.w = rect.w; r.h = rect.h;
			SDL_Point p;
			p.x = rect.w >> 1;
			p.y = rect.h >> 1;
			SDL_RenderCopyEx(ui::Render, texture, &rect, &r, angle, &p, SDL_FLIP_NONE);
		}
};

#endif
