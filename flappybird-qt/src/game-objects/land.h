#include<QPixmap>
#include<QPainter>

#ifndef LAND_H
#define LAND_H

class Land {
	static QPixmap *image;

public:
	int x = 0;

	Land();
	void paint(QPainter* painter) const;
};

#endif
