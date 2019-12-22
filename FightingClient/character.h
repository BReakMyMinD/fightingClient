#pragma once
#include <QGraphicsRectItem>
#include "qnumeric.h"
#include <QDataStream>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include <QDebug>







class Character : public QObject , public QGraphicsPixmapItem {
public:
	Character();
	
	struct charData {
		qint16 x, y, vx, vy;
		qint8 hp, hit;
	} data;

	friend QDataStream &operator >> (QDataStream& stream, charData& item) {
		stream >> item.x >> item.y >> item.vx >> item.vy >> item.hp >> item.hit;
		return stream;
	}

	void updateData(charData newdata);

	QPixmap* defaultSprite, *hitSprite, *jumpSprite;
	QGraphicsTextItem *infoBar;
	QTimer* defaultSpriteTimer;

	void paint(QPainter * _sprite, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;

private slots:
	void nextSpriteFrame();

private:
	qint16 defaultSpriteCounter;
};

//Q_CORE_EXPORT QDataStream &operator >> (QDataStream& stream, charData& item);