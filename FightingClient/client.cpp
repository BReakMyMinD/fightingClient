#include "client.h"
#include "types.h"
#include "character.h"
#include <QPixmap>


//gamewindow methods

GameWindow::GameWindow() {

	player = new Character();
	opponent = new Character();
	player->sprite = new QPixmap("./staticFiles/images.png");
	opponent->sprite = new QPixmap("./staticfiles/images.png");
	this->addItem(player);
	this->addItem(opponent);
	//player->setFlag(QGraphicsItem::ItemIsFocusable);
	//player->setFocus();
	view = new QGraphicsView(this);
	view->show();
	view->setFixedSize(800, 600);
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

void GameWindow::updateGame(QPair<Character, Character>& data) {
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
	_statusLabel->setText("lobby created");
}

void Launcher::lobbyJoined() {
	this->setVisible(false);
	_game = new GameWindow();
	connect(_net, &Network::gameUpdated, _game, &GameWindow::updateGame);
	connect(_game, &GameWindow::keyPressed, _net, &Network::keyPress);
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

//network methods

Network::Network() {
	_socket = new QTcpSocket(this);
	connect(_socket, &QTcpSocket::readyRead, this, &Network::readData);
	in.setDevice(_socket);
	in.setVersion(QDataStream::Qt_5_9);
}

void Network::readData() {

	in.startTransaction();

	qint8 code;
	in >> code;

	if (!in.commitTransaction()) {
		return;
	}
	
	switch (code) {
	case LOBBY_LIST_GOT: {
		
		//setMenuOptionsVisible(false, false);
		QStringList list;
		in >> list;
		//_lobbyList->addItems(list);
		//connect(_lobbyList, &QListWidget::itemClicked, this, &Launcher::lobbySelected);
		//_createLobbyButton->hide();
		//_joinLobbyButton->hide();
		//_nameField->hide();
		emit lobbyListGot(list);
		break;
	}
	case LOBBY_CREATED: {
		//setMenuOptionsVisible(true, false);
		int status;
		in >> status;
		emit lobbyCreated();
		//_statusLabel->setText("lobby successfully created");
		break;
	}
	case LOBBY_JOINED: {
		int status;
		in >> status;
		/*_statusLabel->setText("players ready, game starts");
		scene = new QGraphicsScene();
		*/
		//scene->setSceneRect(0, 0, 800, 600);
		emit lobbyJoined();
		break;
	}
	case GAME_UPDATE: {
		QPair<Character, Character> gameData;
		in >> gameData;
		//player1->setPos(gameData.first.x, gameData.first.y);
		emit gameUpdated(gameData);
		break;
	}
	case GAME_END: {
		QString msg;
		in >> msg;
		//_statusLabel->setText("Player" + disconnectedPlayerName + "left");
		emit gameEnded(msg);
		break;
	}
	/*case SERVER_ERROR: {
		QString errorMessage;
		in >> errorMessage;
		_statusLabel->setText(errorMessage);
		break;
	}*/
	}
}

template<class T>
void Network::writeData(qint8 code, T data) { //T - только сериализуемые qt типы данных! https://doc.qt.io/qt-5/datastreamformat.html
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_9);
	out << code << data;
	_socket->write(block);
}

void Network::connectToServer(QString& ip, int port) {
	if (_socket->state() == QTcpSocket::ConnectedState) {
		_socket->disconnect();
	}
	_socket->connectToHost(ip, port);
	if (_socket->waitForConnected()) {
		return;
	}
	else {
		emit error("Connection failed");
	}
}

void Network::getLobbyList(QString& name) {
	writeData<QString>(GET_LOBBY_LIST, name);
}

void Network::createLobby(QString& name) {
	writeData<QString>(CREATE_LOBBY, name);
}

void Network::joinLobby(int id) {
	writeData<int>(JOIN_LOBBY, id);
}

void Network::keyPress(int key) {
	writeData<int>(KEY_PRESS, key);
}