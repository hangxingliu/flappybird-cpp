#include <QtMath>

#include "./collision.h"

CollisionPoints::CollisionPoints():
	CollisionPoints(0) {}

CollisionPoints::CollisionPoints(unsigned size):
	size(size) {

	if(size > 0) {
		x = new double[size];
		y = new double[size];
	}
}

CollisionPoints::CollisionPoints(const QPixmap& source) {
	QImage img = source.toImage();
	unsigned h = img.height() > 0 ? ((unsigned)img.height()) : 0;
	unsigned w = img.width() > 0 ? ((unsigned)img.width()) : 0;

	double cx = 0.5 * w, cy = 0.5 * h;
	char *alpha = new char[w * h];
	for(unsigned y = 0 ; y < h ; y ++ )
		for(unsigned x = 0; x < w ; x ++ )
			alpha[y * w + x] = img.pixelColor(x, y).alpha() > 0 ? 1 : 0;

	this->count = 0;
	this->size = w * h;
	if(w > 0 && h > 0) {
		this->x = new double[size];
		this->y = new double[size];
	}

	for(unsigned y = 0 ; y < h ; y ++ ) {
		char* row = alpha + y * w;
		char* lastRow = y > 0 ? (alpha + (y - 1) * w) : nullptr;
		char* nextRow = y < (h - 1) ? (alpha + (y + 1) * w) : nullptr;

		for(unsigned x = 0; x < w ; x ++ ) {
			if(row[x] == 0)
				continue;

			// it is a border pixel
			if(x == 0 || x >= (w - 1) || lastRow == nullptr || nextRow == nullptr ||
				// or has a empty content neighbor
				row[x - 1] == 0 || row[x + 1] == 0 ||
				lastRow[x] == 0 || nextRow[x] == 0) {

				this->x[count] = ((int)x) - cx;
				this->y[count] = ((int)y) - cy;
				count ++;
			}
		}
	}

	delete[] alpha;
}

void CollisionPoints::cloneFrom(const CollisionPoints &from) {
	this->~CollisionPoints();

	this->size = from.size;
	this->count = from.count;
	if(from.size > 0) {
		x = new double[size];
		y = new double[size];
		memcpy(x, from.x, sizeof(double) * count);
		memcpy(y, from.y, sizeof(double) * count);
	}
}

CollisionPoints::CollisionPoints(const CollisionPoints& from) {
	cloneFrom(from); }

CollisionPoints& CollisionPoints::operator = (const CollisionPoints& from) {
	cloneFrom(from);
	return *this;
}

CollisionPoints::~CollisionPoints() {
	if(size == 0) return;
	if(x != nullptr) delete[] x;
	if(y != nullptr) delete[] y;
	x = nullptr;
	y = nullptr;
}

void CollisionPoints::rotate(double angle) {
	double rad = qDegreesToRadians(angle),
		cosv = qCos(rad), sinv = qSin(rad);

	double tmpX, tmpY;
	for(unsigned i = 0 ; i < count ; i ++ ) {
		tmpX = x[i] * cosv - y[i] * sinv;
		tmpY = x[i] * sinv + y[i] * cosv;
		x[i] = tmpX; y[i] = tmpY;
	}
}

template<typename T>
T _max(T a, T b) { return a > b ? a : b; }
template<typename T>
T _min(T a, T b) { return a < b ? a : b; }

bool CollisionPoints::detect(const QPoint &center, int boxX1, int boxY1, int boxX2, int boxY2) {
	int maxX = _max(boxX1, boxX2), maxY = _max(boxY1, boxY2),
		minX = _min(boxX1, boxX2), minY = _min(boxY1, boxY2);

	int cx = center.x(), cy = center.y();
	for(unsigned i = 0 ; i < count ; i ++ ) {
		int tx = cx + x[i], ty = cy + y[i];
		if(tx < maxX && tx > minX && ty < maxY && ty > minY) {
			lastCollision = QPointF(cx + x[i], cy + y[i]);
			return true;
		}
	}
	return false;
}

const QPointF& CollisionPoints::getLastCollisionPoint() const { return lastCollision; }

const QList<QPointF> CollisionPoints::getAllPoints(const QPoint &center) const {
	QList<QPointF> points;
	int cx = center.x(), cy = center.y();
	for(unsigned i = 0 ; i < count ; i ++ )
		points.push_back(QPointF(cx+x[i], cy+y[i]));
	return points;
}
