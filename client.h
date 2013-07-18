#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSslSocket>

class Client : public QObject
{
  Q_OBJECT
public:
  Client();
  void sockConnect();
private slots:
  void waitForGreeting();

private:
  QSslSocket *socket;
};

#endif // CLIENT_H
