#include<QPixmap>
#include<QPainter>

#ifndef BG_H
#define BG_H

class Bg {
public:

	static QPixmap *image;

	Bg();
	void paint(QPainter* painter, unsigned counter) const;
};

#endif
