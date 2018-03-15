#include <QApplication>

#include <QtGlobal>
#include <QStyle>
#include <QDebug>
#include <QDesktopWidget>

#include "./src/game-canvas.h"
#include "./src/game-status.h"
#include "./src/utils.h"
#include "./config.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	utils::initRand();

	GameCanvas canvas;
	canvas.setWindowTitle(config::TITLE);
	canvas.show();

	canvas.setMinimumSize(config::GAME_WIDTH, config::GAME_HEIGHT);

	#ifdef Q_OS_ANDROID
		canvas.resize(a.desktop()->availableGeometry().size());
	#else
		canvas.resize(config::GAME_WIDTH, config::GAME_HEIGHT);
		canvas.setGeometry(
			QStyle::alignedRect(
				Qt::LeftToRight,
				Qt::AlignCenter,
				canvas.size(),
				a.desktop()->availableGeometry()
			)
		);
	#endif

	GameStatus status;
	canvas.bindGameStatus(&status);

	return a.exec();
}
