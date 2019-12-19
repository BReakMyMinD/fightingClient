#include "character.h"

Character::Character() {
	defaultSpriteTimer = new QTimer(this);
	connect(defaultSpriteTimer, &QTimer::timeout, this, &Character::nextSpriteFrame);
	defaultSpriteTimer->start(400);
}

void Character::nextSpriteFrame() {
	if (defaultSpriteCounter == 0) {
		defaultSpriteCounter = 160;//
	}
	else {
		defaultSpriteCounter = 0;
	}
}

void Character::update(Character::charData newdata) {
	data = newdata;
	setPos(data.x, data.y);
	
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

	if (data.vy != 0) {
		painter->drawPixmap(0, 0, *jumpSprite, 0, 0, 74, 220);
	}
	else {
		painter->drawPixmap(0, 0, *defaultSprite, defaultSpriteCounter, 0, 160, 220);
	}

	Q_UNUSED(option);

	Q_UNUSED(widget);
}

QRectF Character::boundingRect() const {
	return QRectF(0, 0, 160, 220);
}

