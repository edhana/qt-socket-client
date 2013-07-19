#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QSslError>
#include <QList>

class Client : public QObject
{
  Q_OBJECT

public:
  Client();
  ~Client();
  void sockConnect();

private slots:
  void connectionConfig();
  void readDataFromServer();
  void connectionClosed();
  void socketError(const QList<QSslError> &errors);
  void connectionError(const QAbstractSocket::SocketError &error);

private:
  QSslSocket *socket;
};

#endif // CLIENT_H
