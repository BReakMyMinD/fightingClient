/* ! \file main.cpp

* \brief ���� �������� ���������� ������� main

* \author besoboi(������� ��������) � BreakMyMind(����� ������)

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




