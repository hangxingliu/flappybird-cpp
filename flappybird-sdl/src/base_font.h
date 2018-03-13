#include <SDL.h>
#include <SDL_ttf.h>

#include "./ui.h"

#ifndef BASE_FONT_HEADER
#define BASE_FONT_HEADER


const SDL_Color COLOR_WHITE = {250, 250, 250		,255};
const SDL_Color COLOR_BLACK = {50 , 50 , 50 		,255};

class Font {
	private:
		TTF_Font *font;
	public:
		Font(int fontSize) {
			font = TTF_OpenFont("../res/font/arial.ttf", fontSize);
		}
		~Font() {
			TTF_CloseFont(font);
		}
		bool draw(const char* str, int x,int y) {
			SDL_Surface* surface = TTF_RenderUTF8_Solid(font, str, COLOR_WHITE);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(ui::Render, surface);

			SDL_FreeSurface(surface);

			SDL_Rect r;
			r.x = x;r.y = y;
			int w = 0,h = 0;
			TTF_SizeUTF8(font,str,&w,&h);
			r.w = w;r.h = h;
			SDL_RenderCopy(ui::Render, texture, NULL, &r);

			SDL_DestroyTexture(texture);
			return true;
		}
};

#endif
