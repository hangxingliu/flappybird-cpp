#include <QtGlobal>
#include <QTime>

#include "./utils.h"
#include "../config.h"

void utils::initRand() {
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
}

int utils::randInt(int low, int high) {
	return qrand() % (high - low) + low;
}

int utils::inRange(int v, int min, int max) {
	if(v < min) return min;
	return v >= max ? max : v;
}


int utils::convertHeightToCanvasY(int height) {
	return config::SKY_HEIGHT - height;
}

int utils::convertCanvasYToHeight(int canvasY) {
	return config::SKY_HEIGHT - canvasY;
}

int utils::convertGameXToCanvasX(int x, int birdX) {
	return x - birdX + config::BIRD_X_OFFSET;
}

int utils::convertCanvasXToGameX(int canvasX, int birdX) {
	return canvasX - config::BIRD_X_OFFSET + birdX;
}

