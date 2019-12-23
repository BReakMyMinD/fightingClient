/* ! \file main.cpp

* \brief Файл содержит реализацию функции main

* \author besoboi(Ильичев Григорий) и BreakMyMind(Исаев Андрей)

* \date 15.10.2019

*/



#include "client.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Launcher w;
	w.show();
	
	return a.exec();
}




