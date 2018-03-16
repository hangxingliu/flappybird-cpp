#include <QDebug>
#include <QOpenGLWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QFont>

#include "game-canvas.h"
#include "../config.h"

QColor GameCanvas::backgroundColor("#F3F4F7");
QColor GameCanvas::skyColor("#66C4CC");

GameCanvas::GameCanvas(QWidget *parent): QOpenGLWidget(parent) {
	startTimer(1000 / config::FPS);
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
	painter.fillRect(0, 0, parentWidth, parentHeight, backgroundColor);

	if(parentWidth > config::GAME_WIDTH || parentHeight > config::GAME_HEIGHT) {
		double scale = 1.0 * parentWidth / gameWidth;
		if(gameHeight * scale > parentHeight)
			scale = 1.0 * parentHeight / gameHeight;

		double offsetX = (parentWidth - gameWidth * scale) * 0.5;
		double offsetY = (parentHeight - gameHeight * scale) * 0.5;
		painter.translate(offsetX, offsetY);

		painter.scale(scale, scale);
	}

	// clip game canvas
	painter.setClipRect(0, 0, gameWidth, gameHeight);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.fillRect(0, 0, gameWidth, gameHeight, skyColor);

	if(this->gameStatus != nullptr)
		this->gameStatus->paint(&painter, counter);

	painter.end();
	counter++;
}

const QList<QString> GameCanvas::DANCING_CODE = { "HANGXINGLIU", "NIGHT", "QUICK" };
void GameCanvas::keyPressEvent(QKeyEvent *event) {
	// qDebug() << "keyPress" << event->key();
	if(event->key() == Qt::Key_Space) { // space
		if(this->gameStatus != nullptr)
			this->gameStatus->click();
		event->accept();
		return;
	} else if(event->key() == Qt::Key_Back) {
		event->accept();
		exit(0);
		return;
	}

	dancing += QKeySequence(event->key()).toString().toUpper();
	for(const QString& code: DANCING_CODE) {
		if(dancing == code) {
			qDebug() << code;
			if(code == "HANGXINGLIU") {
				config::PIPE_GAP *= 2;
			} else if(code == "NIGHT") {
				skyColor = QColor("#008793");
				QImage image = Bg::image->toImage();
				int w = image.width(), h = image.height();
				for(int y = 0; y < h ; y ++ ) {
					for(int x = 0; x < w ; x ++ ) {
						QColor color = image.pixelColor(x, y);
						image.setPixelColor(x, y, color.dark(150));
					}
				}
				delete Bg::image;
				Bg::image = new QPixmap(QPixmap::fromImage(image));
			} else if(code == "QUICK") {
				config::BIRD_SPEED = 4;
				config::PIPE_BETWEEN = 400;
			}
			return;
		} else if(code.startsWith(dancing)) {
			return;
		}
	}
	dancing = "";
}

void GameCanvas::mousePressEvent(QMouseEvent *event) {
//	 qDebug() << "mousePress" << event->button();
	if(this->gameStatus == nullptr)
		return;

	switch(event->button()) {
		case Qt::LeftButton:
			this->gameStatus->click();
			break;
		case Qt::RightButton:
			this->gameStatus->rightClick();
			break;
	}
}

