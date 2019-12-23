/* ! \file character.h

* \brief Файл содержит описание класса Character

* \author besoboi(Ильичев Григорий) и BreakMyMind(Исаев Андрей)

* \date 22.12.2019

*/



#pragma once
#include <QGraphicsRectItem>
#include "qnumeric.h"
#include <QDataStream>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QProgressBar>
#include <QGraphicsProxyWidget>







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
	QProgressBar *infoBar;
	QTimer* defaultSpriteTimer;
	QGraphicsProxyWidget* proxy;

	void paint(QPainter * _sprite, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;

private slots:
	void nextSpriteFrame();

private:
	qint16 defaultSpriteCounter;
};

