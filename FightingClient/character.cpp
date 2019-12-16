#include "character.h"

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

	painter->drawPixmap(0, 0, *sprite, 0, 0, 56, 120);

	Q_UNUSED(option);

	Q_UNUSED(widget);
}

QRectF Character::boundingRect() const {
	return QRectF(0, 0, 56, 120);
}

