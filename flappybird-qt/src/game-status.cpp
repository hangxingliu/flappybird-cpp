#include <QDebug>
#include "../config.h"

#include "./utils.h"
#include "./game-status.h"
#include "./game-objects/outline-text.h"

void GameStatus::play() {
	gameStage = STAGE_PLAYING;
	objBird.resetToGameStart();
	score = 0;

	GameStatusThread* thread = GameStatusThread::getThread(this);
	if(thread == nullptr) {
		qDebug() << "Could not start game because thread(GameStatusHandler) is nullptr!";
		return;
	}
	thread->start();

	pipeMaxX = config::PIPE_FIRST_X;
	for(unsigned i = 0 ; i < PIPE_COUNT ; i ++, pipeMaxX += config::PIPE_BETWEEN ) {
		pipeX[i] = pipeMaxX;
		pipeGapY[i] = utils::randInt(config::PIPE_GAP_MIN_HEIGHT, config::PIPE_GAP_MAX_HEIGHT);
		pipeAddedScore[i] = false;
	}
}

void GameStatus::paintAndMovePipes(QPainter *painter) {
	for(unsigned i = 0 ; i < PIPE_COUNT ; i ++ ) {
		int xOffset = pipeX[i] - objBird.x + config::BIRD_X_OFFSET;
		objPipes[i].paint(painter, xOffset, pipeGapY[i]);

		if(!pipeAddedScore[i] && pipeX[i] < objBird.x) {
			pipeAddedScore[i] = true;
			score ++;
		}

		if(gameStage == STAGE_PLAYING && xOffset < - config::PIPE_WIDTH - 10) {
			pipeX[i] = pipeMaxX;  pipeMaxX += config::PIPE_BETWEEN;
			pipeGapY[i] = utils::randInt(config::PIPE_GAP_MIN_HEIGHT, config::PIPE_GAP_MAX_HEIGHT);
			pipeAddedScore[i] = false;
		}
	}
}

void GameStatus::paint(QPainter *painter) {
	painter->save();

	int centerX = config::GAME_WIDTH >> 1;
	int centerY = config::GAME_HEIGHT >> 1;

	objBg.paint(painter);
	if(gameStage != STAGE_PREPARE)
		paintAndMovePipes(painter);
	objBird.paint(painter);
	objLand.paint(painter);

	if(gameStage == STAGE_PLAYING) {
		OutlineText::paint(painter,
			centerX, config::PLAYING_SCORE_Y + objFont.getHeightMd(), 3,
			QString::number(score), objFont.getMd(),
			Qt::white, Qt::black,
			true, 3, 3);
	}else {
		if(gameStage == STAGE_DEAD) {
			OutlineText::paintWhiteBlack(painter,
				centerX, centerY - objFont.getHeightLg(), 3,
				"SCORE:", objFont.getSm(), true, 2, 2);

			OutlineText::paintWhiteBlack(painter,
				centerX, centerY + objFont.getHeightSm(), 5,
				QString::number(score), objFont.getLg(), true, 8, 8);
		} else {
			OutlineText::paint(painter,
				centerX, centerY + 100, 3,
				"\"SPACE\" TO START!",
				#ifdef Q_OS_ANDROID
					objFont.getXs(),
				#else
					objFont.getMd(),
				#endif
				QColor("#ECFBDE"), QColor("#543846"), true, 5, 5);
		}
	}

	// ===== author name =========

	painter->setFont(objFont.getXs());
	painter->drawText(QRect(0, config::SKY_HEIGHT + 30, config::GAME_WIDTH - 5, config::LAND_HEIGHT),
		Qt::AlignTop|Qt::AlignRight,
		"Author: LiuYue @hangxingliu");

	painter->restore();
}

void GameStatus::playingCalculate(int counter) {
	if((counter & 3) == 0) objBird.nextFrame();

	objBird.moveAStep();
	objLand.x += config::BIRD_SPEED;


	if(objBird.heightFromLand <= 0) {
		objBird.angle = 90;
		return setStatusToDead();
	}

	if(config::RUSH) return;

	const int MAX_ALLOW_HEIGHT = config::SKY_HEIGHT + config::MAX_OVERFLOW_HEIGHT;
	if(objBird.heightFromLand >= MAX_ALLOW_HEIGHT)
		objBird.heightFromLand = MAX_ALLOW_HEIGHT;

	int birdW = Bird::width(), birdH = Bird::height();
	if(birdW > 0 && birdH > 0) {
		auto collision = objBird.getCollisionPoints();
		if(collision) {
			CollisionPoints rCollision(*collision);
			rCollision.rotate(objBird.angle);

			QPoint center(objBird.x, objBird.heightFromLand);

			int pipeW = config::PIPE_WIDTH, pipeH = objPipes[0].pipeDown.height();
			for(unsigned i = 0 ; i < PIPE_COUNT ; i ++ ) {
				int gapHeight = utils::convertCanvasYToHeight(pipeGapY[i]);
				int x1 = pipeX[i], x2 = x1 + pipeW;

				if(rCollision.detect(center, x1, gapHeight, x2, gapHeight + pipeH) || // pipe-down
					rCollision.detect(center, x1, gapHeight - config::PIPE_GAP, // pipe-up
						x2, gapHeight - config::PIPE_GAP - pipeH)) {
					return setStatusToDead();
				}
			}
		}

	}

}

void GameStatus::onClick() {
	if(gameStage == STAGE_DEAD) {
		// delay to display score
		if(afterDeadTimer.tick() < 1500)
			return;

		objBird.resetToGameStart();
		gameStage = STAGE_PREPARE;
		return;
	}

	if(gameStage == STAGE_PREPARE )
		this->play();

	objBird.v = config::BIRD_CLICK_UP_V;
}

void GameStatus::setStatusToDead() {
	gameStage = STAGE_DEAD;
	afterDeadTimer.reset();
}

GameStatusThread* GameStatusThread::singleInstance = nullptr;
GameStatusThread* GameStatusThread::getThread(GameStatus *status) {
	if(!status)
		return nullptr;
	if(singleInstance) {
		if(singleInstance->hadStop) {
			delete singleInstance;
			return singleInstance = new GameStatusThread(status);
		}
		return nullptr;
	}
	return singleInstance = new GameStatusThread(status);
}

void GameStatusThread::run() {
	int counter = 0;
	while(!shouldIStop()) {
		status->playingCalculate(counter++);

		if(status->gameStage != STAGE_PLAYING)
			break;
		QThread::msleep(config::CYCLE);
	}
	hadStop = true;
	qDebug() << "GameStatusHandler stop";
}
