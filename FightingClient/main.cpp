#include "client.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Client w;
	w.show();
	
	return a.exec();
}




/*int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QGraphicsScene * scene = new QGraphicsScene();
	rectClass * rect = new rectClass();
	rect->setRect(0, 0, 100, 100);
	scene->addItem(rect);
	rect->setFlag(QGraphicsItem::ItemIsFocusable);
	rect->setFocus();
	QGraphicsView * view = new QGraphicsView(scene);
	view->show();
	return a.exec();
}
*/