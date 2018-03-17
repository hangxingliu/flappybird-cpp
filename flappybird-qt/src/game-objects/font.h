#include<QPainter>
#include<QFont>

#ifndef FONT_H
#define FONT_H

class Font {
	static const QString FONT_FILE;
	static bool load;
	static QString fontFamilyName;

	static QFont fontXs;
	static QFont fontSm;
	static QFont fontMd;
	static QFont fontLg;

	static double heightXS, heightSm, heightMd, heightLg;
	static double testHeight(const QFont& font);

public:
	Font();
	const QFont& getXs();
	const QFont& getSm();
	const QFont& getMd();
	const QFont& getLg();

	double getHeightXS();
	double getHeightSm();
	double getHeightMd();
	double getHeightLg();
};

#endif
