#include<QPixmap>
#include<QPainter>
#include<QPainterPath>
#include<QColor>

#ifndef OUTLINE_TEXT_H
#define OUTLINE_TEXT_H

class OutlineText {
public:
	static void paintWhiteBlack(QPainter *painter,
		int centerX, int centerY, int outlineWidth,
		const QString &text, const QFont &font,
		bool shadow = false, int shadowOffsetX = 0, int shadowOffsetY = 0);

	static void paint(QPainter* painter,
		int centerX, int centerY, int outlineWidth,
		const QString& text, const QFont &font,
		const QColor& inside, const QColor& outline,
		bool shadow = false, int shadowOffsetX = 0, int shadowOffsetY = 0);
};

#endif
