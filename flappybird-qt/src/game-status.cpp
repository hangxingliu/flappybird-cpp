#include <QDebug>
#include "../config.h"

#include "./utils.h"
#include "./game-status.h"
#include "./game-objects/outline-text.h"

void GameStatus::play() {
	playingTimerId = startTimer(config::CYCLE);

	boolIsPlaying = true;
	boolIsDead = false;
	birdHeight = config::BIRD_INIT_HEIGHT;
	birdX = 0;
	birdAngle = 0;
	score = 0;
	v = 0;

	pipeMaxX = config::PIPE_FIRST_X;
	for(unsigned i = 0 ; i < PIPE_COUNT ; i ++, pipeMaxX += config::PIPE_BETWEEN ) {
		pipeX[i] = pipeMaxX;
		pipeGapY[i] = utils::randInt(config::PIPE_GAP_MIN_HEIGHT, config::PIPE_GAP_MAX_HEIGHT);
		pipeAddedScore[i] = false;
	}
}

void GameStatus::paintAndMovePipes(QPainter *painter, unsigned counter) {
	for(unsigned i = 0 ; i < PIPE_COUNT ; i ++ ) {
		int xOffset = pipeX[i] - birdX + config::BIRD_X_OFFSET;
		objPipes[i].paint(painter, counter, xOffset, pipeGapY[i]);

		if(!pipeAddedScore[i] && pipeX[i] < birdX) {
			pipeAddedScore[i] = true;
			score ++;
		}

		if(boolIsPlaying && xOffset < - config::PIPE_WIDTH - 10) {
			pipeX[i] = pipeMaxX;  pipeMaxX += config::PIPE_BETWEEN;
			pipeGapY[i] = utils::randInt(config::PIPE_GAP_MIN_HEIGHT, config::PIPE_GAP_MAX_HEIGHT);
			pipeAddedScore[i] = false;
		}
	}
}

void GameStatus::paint(QPainter *painter, unsigned counter) {
	if(defaultFont == nullptr)
		defaultFont = new QFont(painter->font());

	int centerX = config::GAME_WIDTH >> 1;
	int centerY = config::GAME_HEIGHT >> 1;

	objBg.paint(painter, counter);

	if(boolIsPlaying || boolIsDead)
		paintAndMovePipes(painter, counter);

	objBird.paint(painter, boolIsDead ? 1 : counter,
		config::BIRD_X_OFFSET, birdHeight, birdAngle);

	objLand.paint(painter, boolIsDead ? 1 : counter);

	if(boolIsPlaying) {
		OutlineText::paint(painter,
			centerX, config::PLAYING_SCORE_Y, 3,
			QString::number(score), objFont.getMd(),
			Qt::white, Qt::black,
			true, 3, 3);
	}

	if(!boolIsPlaying) {
		if(boolIsDead) {
			OutlineText::paintWhiteBlack(painter,
				centerX, centerY - 100, 3,
				"SCORE:", objFont.getSm(), true, 2, 2);

			OutlineText::paintWhiteBlack(painter,
				centerX, centerY, 5,
				QString::number(score), objFont.getLg(), true, 8, 8);
		} else {
			OutlineText::paint(painter,
				centerX, centerY + 100, 3,
				"\"SPACE\" TO START!", objFont.getMd(),
				QColor("#ECFBDE"), QColor("#543846"), true, 5, 5);
		}
	}

	// ===== author name =========

	painter->setFont(objFont.getXs());
	painter->drawText(QRect(0, 0, config::GAME_WIDTH - 5, config::GAME_HEIGHT - 5),
		Qt::AlignBottom|Qt::AlignRight,
		"Author: LiuYue @hangxingliu");

	painter->setFont(*defaultFont);
	// ===== finish painting =====

	if(!debug)
		return;

	// ======= debug info =======
	const int PADDING = 10, PADDING2 = PADDING * 2;
	QRect debugTextArea(PADDING, PADDING, config::GAME_WIDTH - PADDING2, config::GAME_HEIGHT - PADDING2);
	QStringList debugInfo;
	debugInfo << "playing: " << (boolIsPlaying ? "true" : "false");
	debugInfo << "dead: " << (boolIsDead ? "true" : "false");
	debugInfo << "score: " << QString::number(score);
	debugInfo << "bird's x: " << QString::number(birdX);
	debugInfo << "bird's h: " << QString::number(birdHeight);
	debugInfo << "bird's v: " << QString::number(v);
	QString debugMessage = "debug:";
	for(int i = 0, i2 = debugInfo.length() ; i < i2 ; i += 2)
		debugMessage += QString("\n  %1%2").arg(debugInfo[i], debugInfo[i+1]);

	painter->drawText(debugTextArea, debugMessage);

	QPen originalPen(painter->pen());

	painter->setPen(QPen(QColor(0, 0, 0, 30), 2));
	for(unsigned i = 100 ; i < config::GAME_HEIGHT ; i += 100 ) {
		painter->drawLine(0, i, config::GAME_WIDTH, i);
		painter->drawText(QRect(0, i, config::GAME_WIDTH, 50),
			Qt::AlignLeft|Qt::AlignTop,
			QString("%1 (h: %2)").arg(
				QString::number(i),
				QString::number(utils::convertCanvasYToHeight(i))));
	}
	for(unsigned i = 100 ; i < config::GAME_WIDTH ; i += 100 ) {
		painter->drawLine(i, 0, i, config::GAME_HEIGHT);
		const int TEXT_HEIGHT = 50, TEXT_WIDTH = 100;
		painter->drawText(QRect(i, config::GAME_HEIGHT - TEXT_HEIGHT,
				TEXT_WIDTH, TEXT_HEIGHT),
			Qt::AlignLeft|Qt::AlignTop,
			QString("%1\nx: %2").arg(
				QString::number(i),
				QString::number(utils::convertCanvasXToGameX(i, birdX))));
	}
	painter->setPen(QPen(Qt::red, 4));
	painter->drawPoint(utils::convertGameXToCanvasX(birdX, birdX),
		utils::convertHeightToCanvasY(birdHeight));

	for(const QRect& rect: debugRects)
		painter->drawRect(rect);

	painter->setPen(QPen(Qt::red, 1));
	for(const QPoint& point: debugPoints)
		painter->drawPoint(point);

	painter->setPen(originalPen);

}

void GameStatus::timerEvent(QTimerEvent*) {
	birdX += config::BIRD_SPEED;

	birdHeight -= v * 0.1;
	v += config::G * 0.1;

	birdAngle = 0;
	if(birdHeight <= 0 ) birdAngle = 90;
	else if(v <= -15) birdAngle = -30;
	else if(v >= 20) birdAngle = 40;
	else birdAngle = v * 2;

	if(birdHeight <= 0) {
		return setStatusToDead();
	}

	int birdW = Bird::width(), birdH = Bird::height();
	if(birdW > 0 && birdH > 0) {
		auto collision = objBird.getCollisionPoints();
		if(collision) {
			CollisionPoints rCollision(*collision);
			rCollision.rotate(birdAngle);

			QPoint center(birdX, birdHeight);

			// // debug display bird border
			// debugPoints.clear();
			// auto points = rCollision.getAllPoints(center);
			// for(const QPointF& p: points) {
			//	debugPoints.push_back(QPoint(
			//		utils::convertGameXToCanvasX(p.x(), birdX),
			//		utils::convertHeightToCanvasY(p.y())));
			//}

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

	const int MAX_ALLOW_HEIGHT = config::SKY_HEIGHT + config::MAX_OVERFLOW_HEIGHT;
	if(birdHeight >= MAX_ALLOW_HEIGHT) {
		birdHeight = MAX_ALLOW_HEIGHT;
	}

}

void GameStatus::click() {
	if(boolIsDead) {
		// delay to display score
		if(afterDeadTimer.tick() < 1500)
			return;
		birdHeight = config::BIRD_INIT_HEIGHT;
		boolIsDead = false;
		birdAngle = 0;
		v = 0;
		return;
	}

	if(!boolIsPlaying)
		this->play();

	v = -45;
}

void GameStatus::setStatusToDead() {
	boolIsPlaying = false;
	boolIsDead = true;
	afterDeadTimer.reset();

	if(this->playingTimerId != 0)
		this->killTimer(this->playingTimerId);
}
