#include <QCoreApplication>
#include <QSslSocket>
#include <QDebug>
#include <QSslError>
#include <QList>

#include "client.h"

int main( int argc, char **argv )
{
    QCoreApplication app( argc, argv );

    Client client;
    client.sockConnect();

    qDebug() << "Done";

    return app.exec();
}
