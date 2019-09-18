#include "client.h"
#include "types.h"

Client::Client(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	_startButton = ui.start;
	_nameField = ui.name;
	_menuWidget = ui.menuWidget;
	connect(_startButton, &QPushButton::released, this, &Client::startGame);
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
			//todo
			break;
		}
	}
}

void Client::startGame() {
	_socket = new QTcpSocket(this);
	connect(_socket, &QTcpSocket::readyRead, this, &Client::readData);
	_socket->connectToHost(_hostAddress, _port);
	if (_socket->waitForConnected()) {
		writeData<QString>(ADD_PLAYER, _nameField->text());
	}
	//_menuWidget->setVisible(0);
}

void Client::readData() {
	in.setDevice(_socket);
	in.setVersion(QDataStream::Qt_5_9);

	in.startTransaction();

	quint8 code;
	in >> code;

	if (!in.commitTransaction()) {
		return;
	}
	
	switch (code) {
	case PLAYER_ADDED: {
		QMap<int, QString> waitingPlayers;
		in >> waitingPlayers;
		
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