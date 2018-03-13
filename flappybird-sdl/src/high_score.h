#include <stdio.h>

#ifndef HIGH_SCORE_HEADER
#define HIGH_SCORE_HEADER

class HighScore {
private:
	int high;
public:
	HighScore() {
		FILE *fp = NULL;
		fp = fopen("score.txt", "r");
		if(fp != NULL) {
			fscanf(fp, "%d", &high);
			fclose(fp);
		} else {
			high = 0;
		}
	}

	int get() { return high; }
	void set(int h) {
		if(h <= high) return;
		FILE *fp = fopen("score.txt", "w");
		fprintf(fp, "%d", h);
		fclose(fp);
		high = h;
	}
};

#endif
