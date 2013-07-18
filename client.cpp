#include <QCoreApplication>
#include <QSslSocket>
#include <QDebug>
#include <QSslError>
#include <QList>
#include "client.h"

Client::Client(){
  socket = new QSslSocket();

  // Signals and Slots
  connect(socket, SIGNAL(connected()), SLOT(connectionConfig()));
  connect(socket, SIGNAL(encrypted()), SLOT(readDataFromServer()));
  connect(socket, SIGNAL(sslErrors(QList<QSslError>)), SLOT(socketError(QList<QSslError>)));
}

Client::~Client(){
    delete socket;
}

void Client::connectionConfig(){
  qDebug() << "TCP Connection Created";

  socket->startClientEncryption();

  if(socket->state() != QAbstractSocket::ConnectedState)
    qDebug() << "There were errors on connection procedure";
  else
    qDebug() << "Client encryption started";

  // Read the server certificate
//  QSslCertificate server_certificate = socket->peerCertificate();

  // TODO: Remover esse codigo daqui
  qDebug() << "Data readed from server: " << socket->readAll().data();
}

void Client::readDataFromServer(){
  qDebug() << "ENCRYPTED CONNECTION STARTED";

  while(socket->waitForReadyRead()){
      qDebug() << "READED DATA: " << socket->readAll().data();
  }
}

void Client::socketError(const QList<QSslError> &errors){
    foreach(const QSslError &error, errors){
        qDebug() << "[ERROR] Error on socket: " << error.errorString();
    }
}

void Client::sockConnect(){
  socket->connectToHost("localhost", 443);
}
