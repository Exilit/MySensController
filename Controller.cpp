#include "Controller.h"
#include "MessageParser.h"

#include <QtNetwork>

Controller::Controller(QObject *parent)
    : QObject(parent)
    , tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, QTcpSocket::connected, this, Controller::connected);
    connect(tcpSocket, QTcpSocket::disconnected, this, Controller::disconnected);
    connect(tcpSocket, QTcpSocket::readyRead, this, Controller::read);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, Controller::showError);
}

Controller::~Controller()
{
}

void Controller::read()
{
    qDebug() << "Ready Read";
    int read;
    char data[1024 * 8];
    data[0] = '\0';

    while((read = tcpSocket->readLine(data, 1024 * 8)) > 0)
    {
        qDebug() << "Read message:" << MessageParser::parseMessage(data);
        m_messageLog << data;
        emit messageLogChanged();
    }
}


void Controller::connected()
{
    qDebug() << "Connected";
    m_messageLog << tr("Connected");
}

void Controller::disconnected()
{
    qDebug() << "Disconnected";
    m_messageLog << tr("Disconnected");
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
