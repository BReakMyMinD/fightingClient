#include "client.h"
//#include "types.h"
//#include "character.h"
#include <QPixmap>


//gamewindow methods

GameWindow::GameWindow() {

	player = new Character();
	opponent = new Character();
	this->addItem(player);
	this->addItem(opponent);
	view = new QGraphicsView(this);
	view->show();
	view->setSceneRect(0, 0, 800, 600);
	view->setFixedSize(800, 600);
}

void GameWindow::setSprites(bool isOwner) {
	if (isOwner) {
		player->sprite = new QPixmap("./staticFiles/left.png");
		opponent->sprite = new QPixmap("./staticfiles/right.png");
		player->setPos(250, 300);
		opponent->setPos(650, 300);
	}
	else {
		opponent->sprite = new QPixmap("./staticFiles/left.png");
		player->sprite = new QPixmap("./staticfiles/right.png");
		player->setPos(650, 300);
		opponent->setPos(250, 300);
	}
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
	int key = event->key();
	switch (key) {
		case Qt::Key_A:
		case Qt::Key_W:
		case Qt::Key_D:
		case Qt::Key_V:
		case Qt::Key_B:
		case Qt::Key_N:
		case Qt::Key_M:
			emit keyPressed(key);
			break;
	}
}

void GameWindow::updateGame(QPair<Character::charData, Character::charData>& data) {
	
	player->setPos(data.first.x, data.first.y);
	opponent->setPos(data.second.x, data.second.y);
}

//launcher methods

Launcher::Launcher(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	_createLobbyButton = ui.createLobby;
	_joinLobbyButton = ui.joinLobby;
	_refreshListButton = ui.refreshList;
	_statusLabel = ui.status;
	_nameField = ui.name;
	_menuWidget = ui.menuWidget;
	_lobbyList = ui.list;
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
	_lobbyList->addItems(list);
	connect(_lobbyList, &QListWidget::itemClicked, this, &Launcher::lobbySelected);
}

void Launcher::lobbyCreated() {
	isOwner = true;
	_statusLabel->setText("lobby created");
}

void Launcher::lobbyJoined() {
	this->setVisible(false);
	_game = new GameWindow();
	connect(_net, &Network::gameUpdated, _game, &GameWindow::updateGame);
	connect(_game, &GameWindow::keyPressed, _net, &Network::keyPress);
	_game->setSprites(isOwner);
}

void Launcher::gameEnded(QString& msg) {
	this->setVisible(true);
	_statusLabel->setText(msg);
	_game->deleteLater();
}

void Launcher::error(QString msg) {
	_statusLabel->setText(msg);
}

//todo
void Launcher::setMenuOptionsVisible(bool isLobbyOwner, bool visible) {
		if (visible) {
			_createLobbyButton->show();
			_joinLobbyButton->show();
			_nameField->show();
			_refreshListButton->hide();
			_lobbyList->hide();
		}
		else {
			if(isLobbyOwner){
				_createLobbyButton->hide();
				_joinLobbyButton->hide();
				_nameField->hide();
				_refreshListButton->hide();
				_lobbyList->hide();
		}
			else {
				_createLobbyButton->hide();
				_joinLobbyButton->hide();
				_nameField->hide();
				_refreshListButton->show();
				_lobbyList->show();
			}
	}
}

void Launcher::createLobby() {
	_net->createLobby(_nameField->text());
}

void Launcher::joinLobby() {
	_net->getLobbyList(_nameField->text());
	//connect(_refreshListButton, &QPushButton::released, this, &Launcher::joinLobby);
}

void Launcher::lobbySelected(QListWidgetItem* item) {
	QString playerNameId = item->text();
	QStringList list = playerNameId.split("#", QString::SkipEmptyParts);
	int playerId = list.last().toInt();
	_net->joinLobby(playerId);
}