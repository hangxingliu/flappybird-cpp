#include <QObject>
#include <QPainter>
#include <QList>
#include <QPoint>

#include "./game-objects/bg.h"
#include "./game-objects/bird.h"
#include "./game-objects/land.h"
#include "./game-objects/pipe.h"
#include "./game-objects/font.h"
#include "../config.h"
#include "./utils.h"

#ifndef GAME_STATUS_H
#define GAME_STATUS_H

class GameStatus: public QObject {

public:
#ifdef QT_DEBUG
	bool debug = true;
#else
	bool debug = false;
#endif

private:
	static const unsigned PIPE_COUNT = 4;

	QList<QRect> debugRects;
	QList<QPoint> debugPoints;

	Bg objBg;
	Bird objBird;
	Land objLand;
	Font objFont;
	PipeCouple objPipes[PIPE_COUNT];

	QFont* defaultFont = nullptr;

	bool boolIsPlaying = false;
	bool boolIsDead = false;
	utils::Timer afterDeadTimer;
	int playingTimerId = 0;

public:
	double v = 0;

	int score = 0;
	int best = 0;

	int birdX = 0;
	int birdHeight = config::BIRD_INIT_HEIGHT;
	int birdAngle = 0;

	int pipeMaxX = -999;
	int pipeGapY[PIPE_COUNT];
	int pipeX[PIPE_COUNT];
	bool pipeAddedScore[PIPE_COUNT];

	void paintAndMovePipes(QPainter* painter, unsigned counter);

	void play();
	void paint(QPainter* painter, unsigned counter);

	explicit GameStatus(QObject *parent = nullptr): QObject(parent) {
		for(unsigned i = 0 ; i < PIPE_COUNT ; i ++) {
			objPipes[i] = PipeCouple();
			pipeX[i] = -999;
			pipeGapY[i] = 0;
			pipeAddedScore[i] = false;
		}
	}
	~GameStatus() {}

	bool isPlaying() { return this->boolIsPlaying; }
	void click();
	void rightClick() { debug = !debug; }

private:
	void setStatusToDead();
	void timerEvent(QTimerEvent *event);
};

#endif // GAME_STATUS_H
