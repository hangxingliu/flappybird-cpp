#include <iostream>

#include "./bird.h"
#include "../../config.h"

using namespace std;

const int Bird::SPEED = 2;

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
	unsigned id = index * ANGLE_COUNT + (unsigned) (angle + 90);
	if(rotatedIamges[id] == nullptr) {
		QMatrix rm;
		rm.rotate(angle);

		QPixmap* image = images[index];
		rotatedIamges[id] = new QPixmap(image->transformed(rm));
	}
	return rotatedIamges[id];
}

Bird::Bird() { }

void Bird::paint(QPainter *painter, unsigned counter, int offset2Left, int height2land, int angle) const {
	// load image
	if(images == nullptr)
		load();

	QPixmap* image = getRotatedImage(angle);
	int x = offset2Left - (image->width() >> 1);
	int y = config::SKY_HEIGHT - height2land - (image->height() >> 1);

	painter->drawPixmap(x, y, image->width(), image->height(), *image);

	if(counter % SPEED == 0)
		nextIndex();
}

CollisionPoints *Bird::getCollisionPoints() const {
	return collisionPoints ? collisionPoints[index] : nullptr;
}

int Bird::width() { return images && images[0] ? images[0]->width() : 0; }
int Bird::height() { return images && images[0] ? images[0]->height() : 0; }
