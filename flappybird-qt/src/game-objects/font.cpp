#include <iostream>

#include <QFontDatabase>
#include <QFont>
#include <QPainterPath>

#include "./font.h"

bool Font::load = false;

const QString Font::FONT_FILE = ":/font.ttf";

QString Font::fontFamilyName("");

QFont Font::fontXs;
QFont Font::fontSm;
QFont Font::fontMd;
QFont Font::fontLg;

double Font::heightXS = 0;
double Font::heightSm = 0;
double Font::heightMd = 0;
double Font::heightLg = 0;


double Font::testHeight(const QFont &font) {
	QPainterPath pp;
	pp.addText(0, 0, font, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\"':@!");
	return pp.boundingRect().height();
}

Font::Font() {
	if(!load) {
		int id = QFontDatabase::addApplicationFont(FONT_FILE);
		if(id < 0) {
			std::cerr << "fatal: could not load `font.ttf from resource!" << std::endl;
			exit(1);
		}

		fontFamilyName = QFontDatabase::applicationFontFamilies(id).at(0);

		fontXs = QFont(fontFamilyName, 10);
		fontSm = QFont(fontFamilyName, 20);
		fontMd = QFont(fontFamilyName, 30);
		fontLg = QFont(fontFamilyName, 60);

		heightXS = testHeight(fontXs);
		heightSm = testHeight(fontSm);
		heightMd = testHeight(fontMd);
		heightLg = testHeight(fontLg);

		load = true;
	}
}

const QFont &Font::getXs() { return fontXs; }
const QFont &Font::getSm() { return fontSm; }
const QFont &Font::getMd() { return fontMd; }
const QFont &Font::getLg() { return fontLg; }


double Font::getHeightXS() { return heightXS; }
double Font::getHeightSm() { return heightSm; }
double Font::getHeightMd() { return heightMd; }
double Font::getHeightLg() { return heightLg; }

