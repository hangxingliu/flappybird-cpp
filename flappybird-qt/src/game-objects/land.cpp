#include <iostream>

#include "./land.h"
#include "../../config.h"

using namespace std;

QPixmap* Land::image = nullptr;

Land::Land() { }

void Land::paint(QPainter *painter, unsigned counter) const {
	// load image
	if(image == nullptr) {
		QPixmap rawImage(":/land.png");
		if(rawImage.isNull()) {
			cerr << "fatal: could not load `land.png` from resource!" << endl;
			exit(1);
		}
		image = new QPixmap(rawImage.scaledToHeight(config::LAND_HEIGHT));
	}

	int offsetX = -((counter * 66 / 10) % config::GAME_WIDTH);
	int offsetY = config::GAME_HEIGHT - image->height();
	int imageW = image->width(), imageH = image->height();

	painter->drawPixmap(offsetX, offsetY, imageW, imageH, *image); offsetX += imageW;
	painter->drawPixmap(offsetX, offsetY, imageW, imageH, *image); offsetX += imageW;
	painter->drawPixmap(offsetX, offsetY, imageW, imageH, *image); offsetX += imageW;
}
