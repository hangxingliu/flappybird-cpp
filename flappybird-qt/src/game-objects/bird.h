#include<QPixmap>
#include<QPainter>

#include "../collision.h"

#ifndef BIRD_H
#define BIRD_H

class Bird {
	static const unsigned IMAGE_COUNT;
	static const unsigned ANGLE_COUNT;

	static QPixmap **images;
	static CollisionPoints **collisionPoints;
	/// rotatedImages[index * 200 + (rotateAngle + 90)];
	static QPixmap **rotatedIamges;



	void load() const;
	QPixmap* getRotatedImage(int angle) const;

	unsigned frameIndex = 0;
public:
	double v = 0;
	int angle = 0;
	int heightFromLand = 0;
	int x = 0;

	Bird();
	void paint(QPainter* painter);
	void resetToGameStart();
	void moveAStep();

	CollisionPoints* getCollisionPoints() const;
	static int width();
	static int height();

	void nextFrame() { frameIndex = frameIndex >= (IMAGE_COUNT - 1) ? 0 : (frameIndex + 1); }
};

#endif
