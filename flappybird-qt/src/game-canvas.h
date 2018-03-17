#include <QOpenGLWidget>
#include <QColor>

#include "./game-status.h"
#include "./unlocker.h"

#ifndef GAME_CANVAS_H
#define GAME_CANVAS_H

class GameCanvas: public QOpenGLWidget {
	static QColor landColor;
	static QColor backgroundColor;
	static QColor skyColor;

	unsigned counter = 0;

	GameStatus* gameStatus = nullptr;

	Unlocker unlocker;
	friend class Unlocker;

public:

	explicit GameCanvas(QWidget *parent = nullptr);
	void bindGameStatus(GameStatus* gameStatus) { this->gameStatus = gameStatus; }

protected:
	void timerEvent(QTimerEvent *event);
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
//#ifdef Q_OS_ANDROID
	void mouseMoveEvent(QMouseEvent *event);
//#endif
};

#endif // GAME_CANVAS_H
