#include <QObject>
#include <QPainter>
#include <QList>
#include <QPoint>
#include <QThread>
#include <QMutex>

#include "./game-objects/bg.h"
#include "./game-objects/bird.h"
#include "./game-objects/land.h"
#include "./game-objects/pipe.h"
#include "./game-objects/font.h"
#include "../config.h"
#include "./utils.h"

#ifndef GAME_STATUS_H
#define GAME_STATUS_H

enum GameStage {
	STAGE_PREPARE = 0,
	STAGE_PLAYING = 1,
	STAGE_DEAD = 2
};

class GameStatus: public QObject {
	friend class GameStatusThread;

public:
#ifdef QT_DEBUG
	bool debug = true;
#else
	bool debug = false;
#endif

private:
	static const unsigned PIPE_COUNT = 4;

	Bg objBg;
	Bird objBird;
	Land objLand;
	Font objFont;
	PipeCouple objPipes[PIPE_COUNT];

	GameStage gameStage = STAGE_PREPARE;
	utils::Timer afterDeadTimer;

public:
	int score = 0;

	int pipeMaxX = -999;
	int pipeGapY[PIPE_COUNT];
	int pipeX[PIPE_COUNT];
	bool pipeAddedScore[PIPE_COUNT];

	void paintAndMovePipes(QPainter* painter);

	void play();
	void paint(QPainter* painter);

	explicit GameStatus(QObject *parent = nullptr): QObject(parent) {
		for(unsigned i = 0 ; i < PIPE_COUNT ; i ++) {
			objPipes[i] = PipeCouple();
			pipeX[i] = -999;
			pipeGapY[i] = 0;
			pipeAddedScore[i] = false;
		}
	}
	~GameStatus() {}

	void onClick();
	void onRightClick() { debug = !debug; }

private:
	void setStatusToDead();
	void playingCalculate(int counter);
};

class GameStatusThread: public QThread {
	static GameStatusThread* singleInstance;

	bool hadStop = false;
	bool tryStop = false;
	GameStatus* status = nullptr;

	QMutex tryStopMutex;
	bool shouldIStop() { QMutexLocker locker(&tryStopMutex); return tryStop; }

	GameStatusThread(GameStatus* status): status(status) {}

public:

	void stop() { QMutexLocker locker(&tryStopMutex); tryStop = true; }
	static GameStatusThread* getThread(GameStatus* status);

	// QThread interface
protected:
	void run();
};



#endif // GAME_STATUS_H
