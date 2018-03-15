#include<QPixmap>
#include<QPainter>

#include "../collision.h"

#ifndef BIRD_H
#define BIRD_H

class Bird {
	static const int SPEED;

	static const unsigned IMAGE_COUNT;
	static const unsigned ANGLE_COUNT;

	static QPixmap **images;
	static CollisionPoints **collisionPoints;
	/// rotatedImages[index * 200 + (rotateAngle + 90)];
	static QPixmap **rotatedIamges;

	mutable unsigned index = 0;
	unsigned nextIndex() const {
		index = index >= (IMAGE_COUNT - 1) ? 0 : (index + 1);
		return index;
	}


	void load() const;
	QPixmap* getRotatedImage(int angle) const;

public:
	Bird();
	void paint(QPainter* painter, unsigned counter, int offset2Left, int height2land, int angle) const;
	CollisionPoints* getCollisionPoints() const;
	static int width();
	static int height();
};

#endif
