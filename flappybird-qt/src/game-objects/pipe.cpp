#include <iostream>

#include "./pipe.h"
#include "../../config.h"

using namespace std;

QPixmap* Pipe::imageUp = nullptr;
QPixmap* Pipe::imageDown = nullptr;

void Pipe::load() {
	if(imageUp == nullptr) {
		QPixmap rawImage(":/pipe-up-longer.png");
		if(rawImage.isNull()) {
			cerr << "fatal: could not load `pipe-up.png` from resource!" << endl;
			exit(1);
		}
		imageUp = new QPixmap(rawImage.scaledToWidth(config::PIPE_WIDTH));
	}
	if(imageDown == nullptr) {
		QPixmap rawImage(":/pipe-down-longer.png");
		if(rawImage.isNull()) {
			cerr << "fatal: could not load `pipe-down.pngg` from resource!" << endl;
			exit(1);
		}
		imageDown = new QPixmap(rawImage.scaledToWidth(config::PIPE_WIDTH));
	}
}

Pipe::Pipe(bool isDown): isDown(isDown) { }

void Pipe::paint(QPainter *painter, int x, int yOffset) const {
	// load image
	load();

	if(isDown) {
		painter->drawPixmap(x, yOffset,
			imageDown->width(), imageDown->height(), *imageDown);
	} else {
		painter->drawPixmap(x ,yOffset,
			imageUp->width(), imageUp->height(), *imageUp);
	}
}

int Pipe::height() const {
	load();
	return isDown ? imageDown->height() : imageUp->height();
}
int Pipe::width() const {
	load();
	return isDown ? imageDown->width() : imageUp->width();
}

void PipeCouple::paint(QPainter *painter, int x, int yGapOffset) const {
	int pipeHeight = pipeDown.height();
	pipeDown.paint(painter, x, yGapOffset - pipeHeight);
	pipeUp.paint(painter, x, yGapOffset + config::PIPE_GAP);

}
