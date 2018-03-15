#include <QPixmap>
#include <QRect>
#include <QPoint>
#include <QList>

#ifndef COLLISION_H
#define COLLISION_H

class CollisionPoints {
	double* x = nullptr;
	double* y = nullptr;
	unsigned count = 0;
	unsigned size = 0;

	QPointF lastCollision;

	void cloneFrom(const CollisionPoints& from);
public:
	CollisionPoints();
	CollisionPoints(unsigned size);
	CollisionPoints(const QPixmap& source);
	CollisionPoints(const CollisionPoints& from);
	CollisionPoints& operator = (const CollisionPoints& from);
	~CollisionPoints();

	void rotate(double angle);
	bool detect(const QPoint& center, int boxX1, int boxY1, int boxX2, int boxY2);

	const QPointF &getLastCollisionPoint() const;
	const QList<QPointF> getAllPoints(const QPoint &center) const;
};

#endif // COLLISION_H

