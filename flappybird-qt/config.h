#include <QString>
#include <QColor>

#ifndef CONFIG_H
#define CONFIG_H

namespace config {
	const int CYCLE = 10;

	const int FPS = 30;

	const int GAME_WIDTH = 480;
	const int GAME_HEIGHT = 720;

	extern int PIPE_GAP;
	extern int PIPE_BETWEEN;
	const int PIPE_WIDTH = 64;
	const int PIPE_FIRST_X = 400;
	const int PIPE_GAP_MIN_HEIGHT = 100;
	const int PIPE_GAP_MAX_HEIGHT = 400;

	const int LAND_HEIGHT = 120;
	const int SKY_HEIGHT = GAME_HEIGHT - LAND_HEIGHT;

	const int MAX_OVERFLOW_HEIGHT = 20;

	extern int BIRD_SPEED;
	const int BIRD_SIZE_HEIGHT = 42;

	const int BIRD_X_OFFSET = (int) (0.45 * GAME_WIDTH);
	const int BIRD_INIT_HEIGHT = (GAME_HEIGHT - LAND_HEIGHT) >> 1;

	const int PLAYING_SCORE_Y = 100;

	const QString TITLE = "Flappy Bird";

	const double G = 9.8;
}


#endif
