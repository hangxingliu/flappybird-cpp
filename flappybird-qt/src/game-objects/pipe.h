#include<QPixmap>
#include<QPainter>

#ifndef PIPE_H
#define PIPE_H

class Pipe {
	static QPixmap *imageDown;
	static QPixmap *imageUp;

	bool isDown;
	char _pad[7];

	static void load();
public:

	Pipe(bool isDown = true);
	void paint(QPainter* painter, unsigned counter, int x, int yOffset) const;
	int height() const;
	int width() const;
};

class PipeCouple {
public:
	Pipe pipeUp;
	Pipe pipeDown;

	PipeCouple(): pipeUp(false), pipeDown(true) {}
	void paint(QPainter* painter, unsigned counter, int x, int yGapOffset) const;
};

#endif
