#include "Controller.h"

#include <QtNetwork>

Controller::Controller(QObject *parent)
    : QObject(parent)
    , tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, QTcpSocket::connected, this, Controller::connected);
    connect(tcpSocket, QTcpSocket::disconnected, this, Controller::disconnected);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, Controller::showError);
}

void Controller::connected()
{
    qDebug() << "Connected";
}

void Controller::disconnected()
{
    qDebug() << "Disconnected";
}

void Controller::showError(QAbstractSocket::SocketError err)
{
    qDebug() << "Error occured:" << err;
}

void Controller::connectToHost(QString host, int port)
{
    if(tcpSocket->isOpen()) {
        tcpSocket->disconnectFromHost();
    }
    tcpSocket->connectToHost(host, port);
}
