#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "./constant.h"
#include "./utils.h"

#ifndef UI_HEADER
#define UI_HEADER

namespace ui{
	//窗口对象
	SDL_Window *Win;

	//窗口主表面
	SDL_Surface *Surface;

	//窗口主渲染器
	SDL_Renderer *Render;


	void init() {
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
			SDL_fatal("SDL_Init");

		//初始化更多图片格式支持
		if(IMG_Init(IMG_INIT_PNG) < 0)
			SDL_fatal("IMG_Init");

		if(TTF_Init() < 0)
			SDL_fatal("TTF_Init");

		// Old solution
		// #include <windows.h>
		// int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
		// int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		SDL_DisplayMode DM;
		const int FIRST_SCREEN = 0;
		SDL_GetCurrentDisplayMode(FIRST_SCREEN, &DM);

		int screenWidth = DM.w;
		int screenHeight = DM.h;
		int winX = (screenWidth - constant::WIN_WIDTH) / 2;
		int winY = (screenHeight - constant::WIN_HEIGHT) / 2;

		//创建窗体
		Win = SDL_CreateWindow(constant::WIN_TITLE,
			winX, winY,
			constant::WIN_WIDTH, constant::WIN_HEIGHT,
			SDL_WINDOW_OPENGL);

		if(Win == nullptr)
			SDL_fatal("SDL_CreateWindow");

		//获得窗体主表面
		Surface = SDL_GetWindowSurface(Win);
		if(Surface == nullptr)
			SDL_fatal("SDL_GetWindowSurface");

		//获得窗体主渲染器
		Render = SDL_CreateRenderer(Win, -1,
			SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC );
		if(Render == nullptr) {
			Render = SDL_GetRenderer(Win);
			if(Render == nullptr)
				SDL_fatal("SDL_CreateRenderer");
		}

		if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl") == SDL_FALSE)
			SDL_fatal("SDL_SetHint(SDL_HINT_RENDER_DRIVER, \"opengl\")");

		if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE)
			SDL_fatal("SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, \"1\")");

//		if(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1) == SDL_FALSE)
//			SDL_fatal("SDL_SetHint(SDL_GL_MULTISAMPLEBUFFERS, 1)");

//		if(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 100) == SDL_FALSE)
//			SDL_fatal("SDL_SetHint(SDL_GL_MULTISAMPLESAMPLES, 100)");
	}

	//退出程序,并且释放SDL相关内容
	void dispose(){
		SDL_FreeSurface(Surface);
		SDL_DestroyRenderer(Render);
		SDL_DestroyWindow(Win);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

}
#endif
