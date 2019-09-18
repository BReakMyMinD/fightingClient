#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVector>
#include <QString>
#include <QMap>
#include <QDebug>
#include <QTcpSocket>
#include <QKeyEvent>
#include <QDataStream>
#include <QWidget>
#include "ui_gui.h"


class Client : public QMainWindow
{
	Q_OBJECT

public:
	Client(QWidget *parent = Q_NULLPTR);
	

private slots:
	void startGame();
	void readData();

private:
	template<class T>
	void writeData(qint8 num, T data);

	void keyPressEvent(QKeyEvent* event);
	Ui::guiClass ui;
	QPushButton* _startButton;
	QDataStream in;
	
	QLineEdit* _nameField;
	QTcpSocket* _socket;
	QWidget* _menuWidget;
	QString _hostAddress = "127.0.0.1";
	int _port = 1234;
};

