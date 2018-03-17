#include <QString>
#include <QList>

#ifndef UNLOCKER_H
#define UNLOCKER_H


class Unlocker {
	static const QList<QString> CODE;
	static const char MOVE_CODE[6];

	QString inputString = "";
	unsigned mmoveCodeIndex = 0;
	char mmoveCode[6] = {0,0,0,0,0,0};

	void unlock(QString code);
public:
	Unlocker();
	void input(int keyCode);
	void mmove(int gw, int gh, int x, int y);
};

#endif // UNLOCKER_H
