#include "network.h"

Network::Network() {
	cmdSocket = new QTcpSocket(this);
	connect(cmdSocket, &QTcpSocket::readyRead, this, &Network::readData);
	in.setDevice(cmdSocket);
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
		qint8 status;
		in >> status;
		emit lobbyCreated();
		//_statusLabel->setText("lobby successfully created");
		break;
	}
	case LOBBY_JOINED: {
		qint32 port;
		in >> port;
		udpPort = port;
		gameSocket = new QUdpSocket(this);
		gameSocket->bind(QHostAddress::AnyIPv4, 3025);
		connect(gameSocket, &QUdpSocket::readyRead, this, &Network::readGameUpdate);
		/*_statusLabel->setText("players ready, game starts");
		scene = new QGraphicsScene();
		*/
		//scene->setSceneRect(0, 0, 800, 600);
		emit lobbyJoined();
		break;
	}
	/*case GAME_UPDATE: {
		QPair<Character, Character> gameData;
		in >> gameData;
		//player1->setPos(gameData.first.x, gameData.first.y);
		emit gameUpdated(gameData);
		break;
	}*/
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

void Network::readGameUpdate() {
	//qDebug() << "hui";
	while (gameSocket->hasPendingDatagrams()) {
		QNetworkDatagram data = gameSocket->receiveDatagram();
		QPair<Character::charData, Character::charData> gameData;
		QDataStream buf(data.data());
		buf >> gameData;
		emit gameUpdated(gameData);
	}
}

template<class T>
void Network::writeData(qint8 code, T data) { //T - ������ ������������� qt ���� ������! https://doc.qt.io/qt-5/datastreamformat.html
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_9);
	if (code == KEY_PRESS && gameSocket != NULL) {
		out << data;
		gameSocket->writeDatagram(block, serverIp, udpPort);
	}
	else {
		out << code << data;
		cmdSocket->write(block);
	}
}

void Network::connectToServer(QString& ip, qint32 port) {
	this->serverIp.setAddress(ip);
	this->tcpPort = port;
	if (cmdSocket->state() == QTcpSocket::ConnectedState) {
		cmdSocket->disconnect();
	}
	cmdSocket->connectToHost(ip, port);
	if (cmdSocket->waitForConnected()) {
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

void Network::joinLobby(qint32 id) {
	writeData<qint32>(JOIN_LOBBY, id);
}

void Network::keyPress(qint16 key) {
	writeData<qint16>(KEY_PRESS, key);
}