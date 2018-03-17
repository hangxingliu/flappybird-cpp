#include <QInputDialog>
#include <QDebug>

#include "unlocker.h"
#include "../config.h"
#include "./game-canvas.h"

const QList<QString> Unlocker::CODE = { "HANGXINGLIU", "NIGHT", "QUICK", "RUSH", "MOON", "ANTI" };
//  1    2
//
//  Center
//
//  4    8
const char Unlocker::MOVE_CODE[6] = {1, 2, 4, 8, 4, 2};

void Unlocker::unlock(QString code) {
	qDebug() << code;
	if(code == "HANGXINGLIU") {
		config::PIPE_GAP *= 2;
	} else if(code == "NIGHT") {
		GameCanvas::skyColor = QColor("#008793");
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
		config::BIRD_X_SPEED_MULTIPLE = 2;
		config::PIPE_BETWEEN = 400;
	} else if(code == "RUSH") {
		config::BIRD_X_SPEED_MULTIPLE = 2;
		config::RUSH = !config::RUSH;
	} else if(code == "MOON") {
		config::PIPE_BETWEEN = 500;
		config::PIPE_FIRST_X = 600;
		config::G = 4.9;
	} else if(code == "ANTI") {
		config::BIRD_ADD_Y_SPEED = 45;
		config::G = -9.8;
	}
}

Unlocker::Unlocker() { }


void Unlocker::input(int keyCode) {
	inputString += QKeySequence(keyCode).toString().toUpper();
	for(const QString& code: CODE) {
		if(inputString == code) {
			unlock(code);
			return;
		} else if(code.startsWith(inputString)) {
			return;
		}
	}
	inputString = "";
}

void Unlocker::mmove(int gw, int gh, int x, int y) {
	int gw10 = gw * 0.15, gh10 = gh * 0.15;

	char code = 0;
	if(x < gw10) {
		if(y < gh10) code = 1;
		else if(y > gh - gh10) code = 4;
	} else if(x > gw - gw10) {
		if(y < gh10) code = 2;
		else if(y > gh - gh10) code = 8;
	}
	if(code == 0)
		return;
	// qDebug() << (int) code;

	if(code == 1) {
		mmoveCode[0] = code;
		mmoveCodeIndex = 1;
		return;
	}
	if(code == mmoveCode[mmoveCodeIndex-1])
		return;

	mmoveCode[mmoveCodeIndex++] = code;
	if(mmoveCodeIndex == 6) {
		if(memcmp(mmoveCode, MOVE_CODE, mmoveCodeIndex) == 0) {
			bool ok = false;
			QString code = QInputDialog::getText(nullptr, "Unlocker",
				"Input code:", QLineEdit::Normal, "", &ok);
			if (ok && !code.isEmpty())
				unlock(code.toUpper());
		}
		mmoveCodeIndex = 0;
	}
}
