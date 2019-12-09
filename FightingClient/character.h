#pragma once
#include <QGraphicsRectItem>
#include "qnumeric.h"
#include <QDataStream>
#include <QGraphicsPixmapItem>
#include <QPainter>







class Character : public QObject , public QGraphicsPixmapItem {
public:
	Character() {};
	
	struct charData {
		qint16 x, y;
		qint8 hp;
	} data;

	friend QDataStream &operator >> (QDataStream& stream, charData& item) {
		stream >> item.x >> item.y >> item.hp;
		return stream;
	}

	QPixmap* sprite;
	void paint(QPainter * _sprite, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
};

//Q_CORE_EXPORT QDataStream &operator >> (QDataStream& stream, charData& item);