#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVector>
#include <QListWidget>
#include <QString>
#include <QMap>
#include <QLabel>
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
	void lobbySelected(QListWidgetItem* item);
	void createLobby();
	void joinLobby();
	void readData();

private:
	template<class T>
	void writeData(qint8 num, T data);

	void startConnection();
	void keyPressEvent(QKeyEvent* event);
	void setMenuOptionsVisible(bool isLobbyOwner, bool visible);
	Ui::guiClass ui;
	QPushButton *_createLobbyButton, *_joinLobbyButton, *_refreshListButton;
	QWidget* _menuWidget;
	QListWidget* _lobbyList;
	QLineEdit* _nameField;
	QLabel* _statusLabel;
	QMap<int, QString> _waitingPlayers;

	QTcpSocket* _socket;
	QDataStream in;
	QString _hostAddress = "127.0.0.1";
	int _port = 1234;
};

