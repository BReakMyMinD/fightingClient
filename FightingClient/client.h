#pragma once
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QString>
#include <QMap>
#include <QLabel>
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
	~GameWindow();
	void setSprites(bool isOwner);
public slots:
	void updateGame(QPair<Character::charData, Character::charData>& data);
signals:
	void keyPressed(qint16 key);
	void keyReleased(qint16 key);
private:
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	Character * player;
	Character * opponent;
	QGraphicsView * view;

	QPixmap *background;
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
	
	Ui::guiClass ui;
	QPushButton *_createLobbyButton, *_joinLobbyButton;
	QWidget* _menuWidget;
	QListWidget* _lobbyList;
	QLineEdit* _nameField;
	QLabel* _statusLabel;
	QMap<int, QString> _waitingPlayers;
	bool isOwner;
	QString _hostAddress = "172.20.10.9";
	int _port = 1234;
};

