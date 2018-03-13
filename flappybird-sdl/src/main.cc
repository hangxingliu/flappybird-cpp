
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//SDL2头文件
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "./constant.h"
#include "./ui.h"
#include "./base_font.h"
#include "./base_image.h"
#include "./high_score.h"
#include "./utils.h"

Image* bg;
Image* image;
Image* imageBoom;
Font* fontStart;
Font* fontScore;

HighScore* highScore;

int wait2start = 0;
bool start = false;
int score = 0;

int boxSize = 50;
int boxSizeHalf = boxSize >> 1;

int x = 60,y = (constant::WIN_HEIGHT >> 1) - boxSizeHalf;
int vy = 0;
int ay = 1;

int boom1x = 0, boom1y = 0;
int boom2x = 0, boom2y = 0;
int boom3x = 0, boom3y = 0;

bool addScore1 = true;
bool addScore2 = true;
bool addScore3 = true;


const int SPLIT_MAX = constant::WIN_HEIGHT - 150;
const int SPLIT_MIN =  100;
const int SPLIT_HEIGHT = 140;

int genRand() {
	return rand() % (SPLIT_MAX + 1 - SPLIT_MIN) + SPLIT_MIN;
}

void drawUI() {
	bg->draw(0,0, 0);

	if(start) {

		int _y = 0;
		for(_y = boom1y - boxSize; _y >= -boxSize ; _y-= boxSize + 5 )
			imageBoom->draw(boom1x, _y);
		for(_y = boom1y + SPLIT_HEIGHT;_y < constant::WIN_HEIGHT + boxSize ; _y += boxSize + 5)
			imageBoom->draw(boom1x, _y);

		for(_y = boom2y - boxSize; _y >= -boxSize ; _y-= boxSize + 5 )
			imageBoom->draw(boom2x, _y);
		for(_y = boom2y + SPLIT_HEIGHT;_y < constant::WIN_HEIGHT + boxSize ; _y += boxSize + 5)
			imageBoom->draw(boom2x, _y);

		for(_y = boom3y - boxSize; _y >= -boxSize ; _y-= boxSize + 5 )
			imageBoom->draw(boom3x, _y);
		for(_y = boom3y + SPLIT_HEIGHT;_y < constant::WIN_HEIGHT + boxSize ; _y += boxSize + 5)
			imageBoom->draw(boom3x, _y);

		image->draw(x, y, (vy << 1) > 45 ? 45 : (vy << 1) );

	}

	char str[30];
	sprintf(str, "%2d   High Score: %2d", score, highScore->get() );
	fontScore->draw(str, 0, 0);
	if(!start) {
		if(wait2start)
			fontStart->draw("You Lose!", 70, 180);
		else
			fontStart->draw("SPACE to start", 40, 180);
	}
}

void handlerLoop() {
	if(!start ) {
		if(wait2start)wait2start --;
		return ;
	}

	boom1x -= 3 ;
	boom2x -= 3 ;
	boom3x -= 3 ;


	if(addScore1 && boom1x < x + 20) {
		addScore1 = false;
		score++;
	}
	if(addScore2 && boom2x < x + 20) {
		addScore2 = false;
		score++;
	}
	if(addScore3 && boom3x < x + 20) {
		addScore3 = false;
		score++;
	}

	if(boom1x < -boxSizeHalf -10) {
		addScore1 = true;
		boom1x = boom3x + constant::WIN_WIDTH * 0.8;
		boom1y = genRand();
	}
	if(boom2x < -boxSizeHalf -10) {
		addScore2 = true;
		boom2x = boom1x + constant::WIN_WIDTH * 0.8;
		boom2y = genRand();
	}
	if(boom3x < -boxSizeHalf -10) {
		addScore3 = true;
		boom3x = boom2x + constant::WIN_WIDTH * 0.8;
		boom3y = genRand();
	}


	y += vy;
	vy += ay;

	y = y < 0 ? 0 : y;

	int cx = x + boxSizeHalf, cy = y + boxSizeHalf;
	if(y > constant::WIN_HEIGHT ||
		hasCollision(cx, cy, 28, boom1x + 25, boom1y) ||
			hasCollision(cx, cy, 28, boom2x + 25, boom2y) ||
				hasCollision(cx, cy, 28, boom3x + 25, boom3y)) {
					highScore->set(score);
					start = false;
					wait2start = 100;
				}

}

void handlerKey() {
	if(!start) {
		if(wait2start)return ;

		start = true;
		score = 0;

		y = (constant::WIN_HEIGHT >> 1) - 25;
		vy = 0;

		boom1x = constant::WIN_WIDTH * 1.8;
		boom2x = constant::WIN_WIDTH * ( 1.8 + 0.8 );
		boom3x = constant::WIN_WIDTH * ( 1.8 + 0.8 * 2 );

		boom1y = genRand();
		boom2y = genRand();
		boom3y = genRand();

		addScore1 = true;
		addScore2 = true;
		addScore3 = true;
		return ;
	}
	if(y > boxSize)
		vy = -10;
}

#define UNUSED(x) (void)(x)

int main(int argc, char* args[]) {
	// unused variables:
	UNUSED(argc);
	UNUSED(args);

	srand( (unsigned int)time(0) );

	ui::init();

	highScore = new HighScore();

	bg = new Image("../res/img/bg.png");
	image = new Image("../res/img/bird.png");
	imageBoom = new Image("../res/img/pipe.png");

	fontStart = new Font(30);
	fontScore = new Font(30);

	bool quit = false;
	SDL_Event e;
	// bool draw = false;
	char loop = 1;
	while(!quit) {
		SDL_Delay(constant::EVENT_INTERVAL);
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			if(e.type == SDL_KEYDOWN &&
				e.key.keysym.sym == SDLK_SPACE) {
				handlerKey();
			}
		}
		if(!(loop % 2))
			handlerLoop();
		loop++;
		//draw = ! draw;
		//if(draw) {
		SDL_SetRenderDrawColor(ui::Render, 255, 0, 0, 255);
		SDL_RenderClear(ui::Render);
		drawUI();
		SDL_RenderPresent(ui::Render);
		//}
	}
	ui::dispose();

	return 0;
}
