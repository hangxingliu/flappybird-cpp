#include <QDebug>

#include <iostream>

#include "./bird.h"
#include "../utils.h"
#include "../../config.h"

using namespace std;

const unsigned Bird::IMAGE_COUNT = 4;
const unsigned Bird::ANGLE_COUNT = 200;

QPixmap** Bird::images = nullptr;
QPixmap** Bird::rotatedIamges = nullptr;
CollisionPoints** Bird::collisionPoints = nullptr;

void Bird::load() const {
	images = new QPixmap*[IMAGE_COUNT];
	collisionPoints = new CollisionPoints*[IMAGE_COUNT];

	const unsigned TOTAL_ROTATED_IMAGES = IMAGE_COUNT * ANGLE_COUNT;
	rotatedIamges = new QPixmap*[TOTAL_ROTATED_IMAGES];
	for(unsigned i = 0 ; i < TOTAL_ROTATED_IMAGES ; i ++ )
		rotatedIamges[i] = nullptr;

	for(unsigned i = 1 ; i <= IMAGE_COUNT ; i ++ ) {
		QPixmap rawImage(QString(":/bird-0%1.png").arg(i));
		if(rawImage.isNull()) {
			cerr << "fatal: could not load `bird-0" << i << ".png` from resource!" << endl;
			exit(1);
		}
		images[i-1] = new QPixmap(rawImage.scaledToHeight(config::BIRD_SIZE_HEIGHT));
		collisionPoints[i-1] = new CollisionPoints(*(images[i-1]));
	}
}

QPixmap* Bird::getRotatedImage(int angle) const {
	if(angle > 90 || angle < -90) {
		cerr << "fatal: angle is invalid (expected: angle <= 90 && angle >= -90, actual: angle = "
			<< angle << ")" << endl;
		exit(1);
	}
	unsigned id = frameIndex * ANGLE_COUNT + (unsigned) (angle + 90);
	if(rotatedIamges[id] == nullptr) {
		QMatrix rm;
		rm.rotate(angle);

		QPixmap* image = images[frameIndex];
		rotatedIamges[id] = new QPixmap(image->transformed(rm));
	}
	return rotatedIamges[id];
}

Bird::Bird() { resetToGameStart(); }

void Bird::paint(QPainter *painter) {
	// load image
	if(images == nullptr)
		load();

	QPixmap* image = getRotatedImage(angle);
	int w = image->width(), h = image->height();
	int x = config::BIRD_X_OFFSET - (w >> 1);
	int y = utils::convertHeightToCanvasY(heightFromLand) - (h >> 1);

	painter->drawPixmap(x, y, w, h, *image);
}

void Bird::resetToGameStart() {
	angle = 0;
	v = 0;
	x = 0;
	heightFromLand = config::BIRD_INIT_HEIGHT;
}

void Bird::moveAStep() {
	x += config::BIRD_SPEED;

	heightFromLand -= v * 0.1;
	v += config::G * 0.1;

	angle = utils::inRange(v * 2, -30, 40);
}

CollisionPoints *Bird::getCollisionPoints() const {
	return collisionPoints ? collisionPoints[frameIndex] : nullptr;
}

int Bird::width() { return images && images[0] ? images[0]->width() : 0; }
int Bird::height() { return images && images[0] ? images[0]->height() : 0; }

