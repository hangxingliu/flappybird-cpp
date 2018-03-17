#include <QDebug>
#include <QOpenGLWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QFont>

#include "game-canvas.h"
#include "../config.h"

QColor GameCanvas::landColor("#DED895");
QColor GameCanvas::backgroundColor("#F3F4F7");
QColor GameCanvas::skyColor("#66C4CC");

GameCanvas::GameCanvas(QWidget *parent): QOpenGLWidget(parent) {
	startTimer(config::DRAW_INTERVAL);
}

void GameCanvas::timerEvent(QTimerEvent *) {
	this->update();
}

void GameCanvas::paintEvent(QPaintEvent *) {
	QPainter painter;
	painter.begin(this);

	int parentWidth = this->width(),
		parentHeight = this->height();
	int gameWidth = config::GAME_WIDTH,
		gameHeight = config::GAME_HEIGHT;

	// draw background
	painter.fillRect(0, 0, parentWidth, parentHeight,
		(parentWidth * config::GAME_HEIGHT / config::GAME_WIDTH) > parentHeight ? backgroundColor : landColor);

	if(parentWidth > config::GAME_WIDTH || parentHeight > config::GAME_HEIGHT) {
		double scale = 1.0 * parentWidth / gameWidth;
		if(gameHeight * scale > parentHeight)
			scale = 1.0 * parentHeight / gameHeight;

		double offsetX = (parentWidth - gameWidth * scale) * 0.5;
		double offsetY = 0; //(parentHeight - gameHeight * scale) * 0.5;

		painter.translate(offsetX, offsetY);

		painter.scale(scale, scale);
	}

	// clip game canvas
	painter.setClipRect(0, 0, gameWidth, gameHeight);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.fillRect(0, 0, gameWidth, gameHeight, skyColor);

	if(this->gameStatus != nullptr)
		this->gameStatus->paint(&painter);

	painter.end();
	counter++;
}

void GameCanvas::keyPressEvent(QKeyEvent *event) {
	auto key = event->key();
	switch(key) {
		case Qt::Key_Space:
			if(this->gameStatus != nullptr)
				this->gameStatus->onClick();
			event->accept();
			return;

		case Qt::Key_Back: // android back button
		case Qt::Key_Escape:
			event->accept();
			exit(0);
			return;
		default:
			unlocker.input(key);
	}
}

void GameCanvas::mousePressEvent(QMouseEvent *event) {
//	 qDebug() << "mousePress" << event->button();
	if(this->gameStatus == nullptr)
		return;

	switch(event->button()) {
		case Qt::LeftButton:
			this->gameStatus->onClick();
			break;
		case Qt::RightButton:
			this->gameStatus->onRightClick();
			break;
	}
}

//#ifdef Q_OS_ANDROID
void GameCanvas::mouseMoveEvent(QMouseEvent *event) {
	unlocker.mmove(this->width(), this->height(), event->x(), event->y());
}
//#endif

