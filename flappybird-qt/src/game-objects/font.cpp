#include <iostream>

#include <QFontDatabase>
#include <QFont>

#include "./font.h"

bool Font::load = false;

const QString Font::FONT_FILE = ":/font.ttf";

QString Font::fontFamilyName("");

QFont Font::fontXs;
QFont Font::fontSm;
QFont Font::fontMd;
QFont Font::fontLg;

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

		load = true;
	}
}

const QFont &Font::getXs() { return fontXs; }
const QFont &Font::getSm() { return fontSm; }
const QFont &Font::getMd() { return fontMd; }
const QFont &Font::getLg() { return fontLg; }

