#include <QtMath>
#include <QPoint>
#include <chrono>

#ifndef UTILS_H
#define UTILS_H

namespace utils {
	void initRand();
	int randInt(int low, int high);

	int convertHeightToCanvasY(int height);
	int convertCanvasYToHeight(int canvasY);
	int convertGameXToCanvasX(int x, int birdX);
	int convertCanvasXToGameX(int canvasX, int birdX);


	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::time_point<Clock> TimePoint;
	typedef std::chrono::milliseconds Ms;
	class Timer {
		TimePoint t1;
		bool started = false;
	public:
		void reset() {
			t1 = Clock::now();
			started = true;
		}
		/// @return milliseonds
		int tick() {
			if(!started) return -1;
			return (int) std::chrono::duration_cast<Ms>(Clock::now() - t1).count();
		}
	};
}

#endif // UTILS_H
