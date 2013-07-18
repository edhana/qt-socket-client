#include <QCoreApplication>
#include <QSslSocket>
#include <QDebug>

#include "client.h"

Client::Client(){
  socket = new QSslSocket();
  connect(socket, SIGNAL(connected()), SLOT(waitForGreeting()));
}

void Client::waitForGreeting(){
  qDebug() << "Que momento emocionante, conectou!!\n";
}

void Client::sockConnect(){
  socket->connectToHost("localhost", 443);

  while(!socket->waitForConnected())
    qDebug() << "Ainda nao conectou!!!";
}

int main( int argc, char **argv )
{
    QCoreApplication app( argc, argv );

    Client client;
    client.sockConnect();

    qDebug() << "Done";

    return 0;
}
