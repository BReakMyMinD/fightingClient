#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QBuffer>
#include <QDataStream>
#include "character.h"
#include "types.h"

class Network : public QObject {
	Q_OBJECT
public:
	Network();
public slots:
	void connectToServer(QString& ip, qint32 port);
	void getLobbyList(QString& name);
	void createLobby(QString& name);
	void joinLobby(qint32 id);
	void keyPress(qint16 key);
private slots:
	void readData();
	void readGameUpdate();
signals:
	void lobbyListGot(QStringList& list);
	void lobbyCreated();
	void lobbyJoined();
	void gameUpdated(QPair<Character::charData, Character::charData>& data);
	void gameEnded(QString& msg);
	void error(QString msg);
private:
	template<class T>
	void writeData(qint8 code, T data);

	QTcpSocket* cmdSocket;
	QUdpSocket* gameSocket;
	QDataStream in;

	qint32 udpPort;
	qint32 tcpPort;
	QHostAddress serverIp;
};