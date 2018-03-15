#include <QOpenGLWidget>
#include <QColor>

#include "./game-status.h"

#ifndef GAME_CANVAS_H
#define GAME_CANVAS_H

class GameCanvas: public QOpenGLWidget {
	static QColor backgroundColor;
	static QColor skyColor;

	unsigned counter = 0;

	GameStatus* gameStatus = nullptr;

	QString dancing = "";
	static const QList<QString> DANCING_CODE;
public:

	explicit GameCanvas(QWidget *parent = nullptr);
	void bindGameStatus(GameStatus* gameStatus) { this->gameStatus = gameStatus; }

protected:
	void timerEvent(QTimerEvent *event);
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
};

#endif // GAME_CANVAS_H
