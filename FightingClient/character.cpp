/* ! \file character.cpp

* \brief Файл содержит реализацию класса Character

* \author besoboi(Ильичев Григорий) и BreakMyMind(Исаев Андрей)

* \date 22.12.2019

*/



#include "character.h"

Character::Character() {
	infoBar = new QProgressBar();
	infoBar->setTextVisible(0);
	defaultSpriteTimer = new QTimer(this);
	connect(defaultSpriteTimer, &QTimer::timeout, this, &Character::nextSpriteFrame);
	defaultSpriteTimer->start(200);
}

void Character::nextSpriteFrame() {
	if (defaultSpriteCounter == 0) {
		defaultSpriteCounter = 160;
	}
	else {
		defaultSpriteCounter = 0;
	}
}

void Character::updateData(Character::charData newdata) {
	data = newdata;
	setPos(data.x, data.y);
	infoBar->setValue(data.hp);
	update();
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	if (data.hit != 0) {
		painter->drawPixmap(0, 0, *hitSprite, 0, 0, 179, 220);
	}
	else {
		if (data.vy != 0) {
			painter->drawPixmap(0, 0, *jumpSprite, 0, 0, 74, 220);
		}
		else {
			if (data.vx != 0) {
				painter->drawPixmap(0, 0, *defaultSprite, defaultSpriteCounter, 0, 160, 220); 
			}
			else {
				painter->drawPixmap(0, 0, *defaultSprite, 0, 0, 160, 220);
			}
		}
	}
	

	Q_UNUSED(option);

	Q_UNUSED(widget);
}

QRectF Character::boundingRect() const {
	return QRectF(0, 0, 180, 220);
}

