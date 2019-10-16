#pragma once
#include <QGraphicsRectItem>
#include "qnumeric.h"
#include <QDataStream>

class Character : public QGraphicsRectItem {
public:
	Character() {
		hp = 100;
		x = 0;
		y = 0;
	};

	//friend QDataStream& operator<<(QDataStream& stream, const Character& character) {
		//return stream << character.x << character.y << character.hp;
	//}
	friend QDataStream& operator >> (QDataStream& stream, Character* character) {
		stream >> character->x >> character->y >> character->hp;
		return stream;
	}

private:
	qint8 x, y, hp;
};

