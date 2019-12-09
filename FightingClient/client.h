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
#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "network.h"
#include "ui_gui.h"






class GameWindow : public QGraphicsScene {
	Q_OBJECT
public:
	GameWindow();
public slots:
	void updateGame(QPair<Character::charData, Character::charData>& data);
signals:
	void keyPressed(int key);
private:
	void keyPressEvent(QKeyEvent* event);
	Character * player;
	Character * opponent;
	QGraphicsView * view;
};

class Launcher : public QMainWindow
{
	Q_OBJECT

public:
	Launcher(QWidget *parent = Q_NULLPTR);
	
public slots:
	void lobbyListGot(QStringList& list);
	void lobbyCreated();
	void lobbyJoined();
	void gameEnded(QString& msg);
	void error(QString msg);

private slots:
	void lobbySelected(QListWidgetItem* item);
	void createLobby();
	void joinLobby();
	

private:
	GameWindow* _game;
	Network* _net;
	
	//void startSession();
	void setMenuOptionsVisible(bool isLobbyOwner, bool visible);
	Ui::guiClass ui;
	QPushButton *_createLobbyButton, *_joinLobbyButton, *_refreshListButton;
	QWidget* _menuWidget;
	QListWidget* _lobbyList;
	QLineEdit* _nameField;
	QLabel* _statusLabel;
	QMap<int, QString> _waitingPlayers;
	//QString _hostAddress = "83.220.170.92";
	QString _hostAddress = "192.168.137.1";
	int _port = 1234;
};

