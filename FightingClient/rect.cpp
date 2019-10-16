
#include "rect.h"
#include <QKeyEvent>
#include <QDebug>
#include <time.h>

void rectClass::keyPressEvent(QKeyEvent * event)
{
	double i = 0;
	int starty = this->y();
	switch (event->key()) {
	case Qt::Key_Left:
		setPos(x() - 10, y());
		break;
	case Qt::Key_Right:
		setPos(x() + 10, y());
		break;
	case Qt::Key_Up:
		this->jump();
	}
}

void rectClass::jump() {
	clock_t start = clock();
	long double startMs = (double)(clock()) / CLOCKS_PER_SEC;
	while (true) {
		double t = (double)(clock() - start) / CLOCKS_PER_SEC;
		if (t > 10) {
			start = clock();
			setPos(x(), y() - 5);
		}
		if (startMs > 1000) break;
	}



	
}