/* ! \file client.cpp

* \brief ���� �������� ���������� ������� GameWindow � Launcher

* \author besoboi(������� ��������) � BreakMyMind(����� ������)

* \date 22.12.2019

*/



#include "client.h"
#include <QPixmap>




//gamewindow methods

GameWindow::GameWindow() {
	player = new Character();
	opponent = new Character();
	background = new QPixmap("./staticFiles/background.jpg");
	this->addItem(player);
	this->addItem(opponent);
	player->proxy = this->addWidget(player->infoBar);
	opponent->proxy = this->addWidget(opponent->infoBar);
	view = new QGraphicsView(this);
	view->show();
	view->setSceneRect(0, 0, 800, 600);
	view->setFixedSize(800, 600);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setBackgroundBrush(background->scaled(800,600));
}

void GameWindow::setSprites(bool isOwner) {
	if (isOwner) {
		player->proxy->setPos(10, 10);
		opponent->proxy->setPos(590, 10);
		player->defaultSprite = new QPixmap("./staticFiles/ken-default.png");
		player->jumpSprite = new QPixmap("./staticFiles/ken-jump.png");
		player->hitSprite = new QPixmap("./staticfiles/ken-hit.png");
		opponent->defaultSprite = new QPixmap("./staticFiles/ryu-default.png");
		opponent->jumpSprite = new QPixmap("./staticFiles/ryu-jump.png");
		opponent->hitSprite = new QPixmap("./staticfiles/ryu-hit.png");
		player->setPos(150, 320);
		opponent->setPos(550, 320);
	}
	else {
		player->proxy->setPos(590, 10);
		opponent->proxy->setPos(10, 10);
		player->defaultSprite = new QPixmap("./staticFiles/ryu-default.png");
		player->jumpSprite = new QPixmap("./staticFiles/ryu-jump.png");
		player->hitSprite = new QPixmap("./staticfiles/ryu-hit.png");
		opponent->defaultSprite = new QPixmap("./staticFiles/ken-default.png");
		opponent->jumpSprite = new QPixmap("./staticFiles/ken-jump.png");
		opponent->hitSprite = new QPixmap("./staticfiles/ken-hit.png");
		player->setPos(550, 320);
		opponent->setPos(150, 320);
	}
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat()) {
		int key = event->key();
		switch (key) {
			case Qt::Key_A:
			case Qt::Key_W:
			case Qt::Key_D:
			case Qt::Key_Space:
			emit keyPressed(key);
			break;
		}
	}
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat()) {
		int key = event->key();
		switch (key) {
		case Qt::Key_A:
		case Qt::Key_D:
			emit keyReleased(key);
			break;
		}
	}
}

GameWindow::~GameWindow() {
	delete view;
	delete player;
	delete opponent;
}

void GameWindow::updateGame(QPair<Character::charData, Character::charData>& data) {
	player->updateData(data.first);
	opponent->updateData(data.second);
}

//launcher methods

Launcher::Launcher(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	_createLobbyButton = ui.createLobby;
	_joinLobbyButton = ui.joinLobby;
	_statusLabel = ui.status;
	_nameField = ui.name;
	_menuWidget = ui.menuWidget;
	_lobbyList = ui.list;

	_lobbyList->hide();

	_net = new Network();
	_net->connectToServer(_hostAddress, _port);
	isOwner = false;

	connect(_createLobbyButton, &QPushButton::released, this, &Launcher::createLobby);
	connect(_joinLobbyButton, &QPushButton::released, this, &Launcher::joinLobby);
	connect(_net, &Network::lobbyListGot, this, &Launcher::lobbyListGot);
	connect(_net, &Network::lobbyCreated, this, &Launcher::lobbyCreated);
	connect(_net, &Network::lobbyJoined, this, &Launcher::lobbyJoined);
	connect(_net, &Network::gameEnded, this, &Launcher::gameEnded);
	connect(_net, &Network::error, this, &Launcher::error);


}

void Launcher::lobbyListGot(QStringList& list) {
	_statusLabel->setText("select lobby from the list");
	_lobbyList->addItems(list);
	connect(_lobbyList, &QListWidget::itemClicked, this, &Launcher::lobbySelected);
	_createLobbyButton->hide();
	_joinLobbyButton->hide();
	_lobbyList->show();
	_nameField->hide();
}

void Launcher::lobbyCreated() {
	isOwner = true;
	_statusLabel->setText("lobby created");
	_lobbyList->hide();
	_createLobbyButton->hide();
	_joinLobbyButton->hide();
	_nameField->hide();
}

void Launcher::lobbyJoined() {
	this->setVisible(false);
	_game = new GameWindow();
	connect(_net, &Network::gameUpdated, _game, &GameWindow::updateGame);
	connect(_game, &GameWindow::keyPressed, _net, &Network::keyPress);
	connect(_game, &GameWindow::keyReleased, _net, &Network::keyRelease);
	_game->setSprites(isOwner);
}

void Launcher::gameEnded(QString& msg) {
	this->setVisible(true);
	_createLobbyButton->show();
	_joinLobbyButton->show();
	_nameField->show();
	_nameField->clear();
	_lobbyList->clear();
	_lobbyList->hide();

	_statusLabel->setText(msg);
	_net->deleteLater();
	_game->deleteLater();
	_net = new Network();
	_net->connectToServer(_hostAddress, _port);
	isOwner = false;

	connect(_net, &Network::lobbyListGot, this, &Launcher::lobbyListGot);
	connect(_net, &Network::lobbyCreated, this, &Launcher::lobbyCreated);
	connect(_net, &Network::lobbyJoined, this, &Launcher::lobbyJoined);
	connect(_net, &Network::gameEnded, this, &Launcher::gameEnded);
	connect(_net, &Network::error, this, &Launcher::error);
}

void Launcher::error(QString msg) {
	_statusLabel->setText(msg);
}

void Launcher::createLobby() {
	_net->createLobby(_nameField->text());
	
}

void Launcher::joinLobby() {
	_net->getLobbyList(_nameField->text());
	
}

void Launcher::lobbySelected(QListWidgetItem* item) {
	QString playerNameId = item->text();
	QStringList list = playerNameId.split("#", QString::SkipEmptyParts);
	int playerId = list.last().toInt();
	_net->joinLobby(playerId);
}