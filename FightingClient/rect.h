#pragma once
#include <QGraphicsRectItem>

class rectClass : public QGraphicsRectItem {
public:
	void keyPressEvent(QKeyEvent * event);
	void jump();
	public slots:
};
