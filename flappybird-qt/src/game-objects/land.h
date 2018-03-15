#include<QPixmap>
#include<QPainter>

#ifndef LAND_H
#define LAND_H

class Land {
	static QPixmap *image;

public:
	Land();
	void paint(QPainter* painter, unsigned counter) const;
};

#endif
