#include <QPainter>
#include <QPainterPath>
#include<QColor>

#include "./outline-text.h"


void OutlineText::paintWhiteBlack(QPainter *painter,
	int centerX, int centerY, int outlineWidth,
	const QString &text, const QFont &font,
	bool shadow, int shadowOffsetX, int shadowOffsetY) {

	paint(painter, centerX, centerY, outlineWidth,
		text, font, Qt::white, Qt::black,
		shadow, shadowOffsetX, shadowOffsetY);
}

void OutlineText::paint(QPainter *painter,
	int centerX, int centerY, int outlineWidth,
	const QString &text,
	const QFont &font,
	const QColor &inside, const QColor &outline,
	bool shadow, int shadowOffsetX, int shadowOffsetY) {

	QPainterPath path;
	painter->save();
	path.addText(0, 0, font, text);

	QRectF rect = path.boundingRect();
	path.translate(centerX - rect.width() * 0.5, centerY - rect.height() * 0.5);

	if(shadow) {
		QPainterPath pathShadow(path);
		pathShadow.translate(shadowOffsetX, shadowOffsetY);
		painter->fillPath(pathShadow, QBrush(outline));
	}

	painter->fillPath(path, QBrush(inside));
	painter->strokePath(path, QPen(outline, outlineWidth));

	painter->restore();

}
