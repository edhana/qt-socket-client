#include <QCoreApplication>
#include <QSslSocket>
#include <QDebug>
#include <QSslError>
#include <QList>
#include "client.h"

Client::Client(){
  socket = new QSslSocket(this);

  // Signals and Slots
  connect(socket, SIGNAL(connected()), SLOT(connectionConfig()));
  connect(socket, SIGNAL(encrypted()), SLOT(readDataFromServer()));
  connect(socket, SIGNAL(disconnected()), SLOT(connectionClosed()));
  connect(socket, SIGNAL(sslErrors(QList<QSslError>)), SLOT(socketError(QList<QSslError>)));
  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(connectionError(QAbstractSocket::SocketError)));
}

Client::~Client(){
    delete socket;
}

void Client::connectionConfig(){
  qDebug() << "TCP Connection Created";

  if(socket->state() != QAbstractSocket::ConnectedState){
    qDebug() << "There were errors on connection procedure";
  }else{
    // Start SSL Handshake
    qDebug() << "Starting SSL Handshake";
    socket->startClientEncryption();
  }
}

void Client::connectionClosed(){
    qDebug() << "The connection with server was closed";
    QCoreApplication::quit();
}

void Client::readDataFromServer(){
  while(socket->waitForReadyRead()){
      qDebug() << "READED DATA: " << socket->readAll().data();
  }
}

void Client::socketError(const QList<QSslError> &errors){
    qDebug() << "Found " << errors.size() << " erros on ssl communication.";

    foreach(const QSslError &error, errors){
        qDebug() << "[ERROR] Error on socket: " << error.errorString();
    }

    // Read the server certificate
    QSslCertificate server_certificate = socket->peerCertificate();

    if(server_certificate.isBlacklisted()){
        qDebug() << "[ERROR] Invalid server";
        return;
    }
    else if(server_certificate.isNull()){
        qDebug() << "[ERROR] Server certificate is NULL";
        return;
    }

    // Debug Certificate information
    qDebug() << "[DEBUG] Date: " << server_certificate.effectiveDate().toString();
    qDebug() << "[DEBUG] Expire: " << server_certificate.expiryDate().toString();

    if(!socket->isEncrypted()){
        qDebug() << "[ERROR] Encrypted connection was not initialized.";
    }
}

void Client::connectionError(const QAbstractSocket::SocketError &error){
    if(error == QAbstractSocket::ConnectionRefusedError){
        qDebug() << "[ERROR] The connection was refused by the server";
    }else if(error == QAbstractSocket::SslHandshakeFailedError){
        qDebug() << "[ERROR] It was not possible to finish the SSL Handshake";
    }else{
        qDebug() << "[ERROR] A connection error has been found: " << error;
    }
}

void Client::sockConnect(){
  socket->connectToHost("localhost", 443);
//    socket->connectToHost("ubuntu", 443);
    if(!socket->waitForConnected()){
        qDebug() << "[ERROR] Could not estabilish connection with server.";
    }
}
