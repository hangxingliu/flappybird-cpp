#include <QString>
#include <QColor>

#ifndef CONFIG_H
#define CONFIG_H

namespace config {
	extern int CALC_INTERVAL;

	extern int DRAW_INTERVAL;

	extern int GAME_WIDTH;
	extern int GAME_HEIGHT;

	extern int PIPE_GAP;
	extern int PIPE_BETWEEN;
	extern int PIPE_WIDTH;
	extern int PIPE_FIRST_X;
	extern int PIPE_GAP_MIN_HEIGHT;
	extern int PIPE_GAP_MAX_HEIGHT;

	extern int LAND_HEIGHT;
	extern int SKY_HEIGHT;

	extern int MAX_OVERFLOW_HEIGHT;

	extern int BIRD_X_SPEED;
	extern int BIRD_X_SPEED_MULTIPLE;
	extern int BIRD_SIZE_HEIGHT;

	extern int BIRD_X_OFFSET;
	extern int BIRD_INIT_HEIGHT;
	extern int BIRD_ADD_Y_SPEED;

	extern int PLAYING_SCORE_Y;

	extern QString TITLE;

	extern double G;

	extern bool RUSH;
}


#endif
