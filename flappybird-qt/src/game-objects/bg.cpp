#include <iostream>

#include "./bg.h"
#include "../../config.h"

using namespace std;

QPixmap* Bg::image = nullptr;

Bg::Bg() { }

void Bg::paint(QPainter *painter, unsigned) const {
	// load image
	if(image == nullptr) {
		QPixmap rawImage(":/sky.png");
		if(rawImage.isNull()) {
			cerr << "fatal: could not load `sky.png` from resource!" << endl;
			exit(1);
		}
		image = new QPixmap(rawImage.scaledToWidth(config::GAME_WIDTH));
	}

	int w = image->width(), h = image->height();
	painter->drawPixmap(0, config::SKY_HEIGHT - h, w, h, *image);
}
