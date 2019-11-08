#pragma once
#include <QGraphicsRectItem>
#include "qnumeric.h"
#include <QDataStream>
#include <QGraphicsPixmapItem>
#include <QPainter>


class Character : public QObject , public QGraphicsPixmapItem {
public:
	Character() {
		hp = 100;
		x = 0;
		y = 0;
	};

	friend QDataStream& operator >> (QDataStream& stream, Character& character) {
		stream >> character.x >> character.y >> character.hp;
		return stream;
	}

	QPixmap* sprite;
	qint8 x, y, hp;
	void paint(QPainter * _sprite, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
};

