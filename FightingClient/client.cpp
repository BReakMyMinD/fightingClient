#include "client.h"
#include "types.h"
#include "character.h"

Client::Client(QWidget *parent)
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
	connect(_createLobbyButton, &QPushButton::released, this, &Client::createLobby);
	connect(_joinLobbyButton, &QPushButton::released, this, &Client::joinLobby);
	startConnection();
	in.setDevice(_socket);
	in.setVersion(QDataStream::Qt_5_9);
}

void Client::keyPressEvent(QKeyEvent* event) {
	if (_socket->state() == QTcpSocket::ConnectedState) {
		switch (event->key()) {
		case Qt::Key_A:
		case Qt::Key_W:
		case Qt::Key_D:
		case Qt::Key_V:
		case Qt::Key_B:
		case Qt::Key_N:
		case Qt::Key_M:
			writeData<int>(KEY_PRESS, event->key());
			break;
		}
	}
}

void Client::setMenuOptionsVisible(bool isLobbyOwner, bool visible) {
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

void Client::createLobby() {
	writeData<QString>(CREATE_LOBBY, _nameField->text());
}

void Client::joinLobby() {
	writeData<QString>(GET_LOBBY_LIST, _nameField->text());
	connect(_refreshListButton, &QPushButton::released, this, &Client::joinLobby);
}

void Client::lobbySelected(QListWidgetItem* item) {
	QString playerNameId = item->text();
	QStringList list = playerNameId.split("#", QString::SkipEmptyParts);
	int playerId = list.last().toInt();
	writeData<int>(JOIN_LOBBY, playerId);
}

void Client::readData() {

	in.startTransaction();

	qint8 code;
	in >> code;

	if (!in.commitTransaction()) {
		return;
	}
	
	switch (code) {
	case LOBBY_LIST_GOT: {
		setMenuOptionsVisible(false, false);
		QStringList list;
		in >> list;
		_lobbyList->addItems(list);
		connect(_lobbyList, &QListWidget::itemClicked, this, &Client::lobbySelected);
		_createLobbyButton->hide();
		_joinLobbyButton->hide();
		_nameField->hide();
		break;
	}
	case LOBBY_CREATED: {
		setMenuOptionsVisible(true, false);
		int status;
		in >> status;
		_statusLabel->setText("lobby successfully created");
		break;
	}
	case LOBBY_JOINED: {
		int status;
		in >> status;
		_statusLabel->setText("players ready, game starts");
		scene = new QGraphicsScene();
		player1 = new Character();
		player2 = new Character();
		player1->setRect(0, 0, 100, 100);
		scene->addItem(player1);
		player1->setFlag(QGraphicsItem::ItemIsFocusable);
		player1->setFocus();
		view = new QGraphicsView(scene);
		view->show();
		break;
	}
	case GAME_UPDATE: {
		QPair<Character, Character> gameData;
		in >> gameData;
		
		break;
	}
	case PLAYER_LEFT: {
		QString disconnectedPlayerName;
		in >> disconnectedPlayerName;
		_statusLabel->setText("Player" + disconnectedPlayerName + "left");
		break;
	}
	case SERVER_ERROR: {
		QString errorMessage;
		in >> errorMessage;
		_statusLabel->setText(errorMessage);
		break;
	}
	}
}

template<class T>
void Client::writeData(qint8 code, T data) { //T - только сериализуемые qt типы данных! https://doc.qt.io/qt-5/datastreamformat.html
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_9);
	out << code << data;
	_socket->write(block);
}

void Client::startConnection() {
	_socket = new QTcpSocket(this);
	connect(_socket, &QTcpSocket::readyRead, this, &Client::readData);
	_socket->connectToHost(_hostAddress, _port);
	_statusLabel->setText("connecting...");
	if (_socket->waitForConnected()) {
		_statusLabel->setText("connected successfully");
		return;
	}
	else {
		_statusLabel->setText("connection failed");
	}
}