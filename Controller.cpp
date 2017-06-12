#include "Controller.h"
#include "MessageParser.h"
#include "BinarySensor.h"

#include <QTcpSocket>
#include <QtNetwork>
#include <QQmlApplicationEngine>

Controller::Controller(QObject *parent)
    : QObject(parent)
    , tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, &QTcpSocket::connected, this, &Controller::connected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Controller::disconnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Controller::read);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &Controller::showError);
}

Controller::~Controller()
{
}

void Controller::send(Message msg)
{
    QString message = msg.toSerialFormat();
    tcpSocket->write(message.toLocal8Bit());
    m_messageLog << QString("<--") + message;
}

void Controller::read()
{
    int read;
    char data[1024 * 8];
    data[0] = '\0';

    while((read = tcpSocket->readLine(data, 1024 * 8)) > 0)
    {
        handleMessage(MessageParser::parseMessage(data));
        m_messageLog << QString("-->") + data;
        emit messageLogChanged();
    }
}


void Controller::connected()
{
    qDebug() << "Connected";
    m_messageLog << tr("Connected");
    emit connectionEstablished();
}

void Controller::disconnected()
{
    qDebug() << "Disconnected";
    m_messageLog << tr("Disconnected");
    emit connectionLost();
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

void Controller::handleMessage(const Message &msg)
{
    switch(msg.command)
    {
    case CommandPresentation:
        handlePresentationMessage(msg);
        break;
    case CommandSet:
        handleSetMessage(msg);
        break;
    case CommandInternal:
        handleInternalMessage(msg);
        break;
    default:
        qWarning() << "Unknown command type" << msg.command << ":" << msg;
    }
}

void Controller::handlePresentationMessage(const Message &msg)
{
    switch(msg.type)
    {
    case SensorBinary:
    {
        qDebug() << QString("Node %1 has Binary Sensor with ID %2").arg(msg.nodeId).arg(msg.childSensorId);
        Sensor *sensor = new BinarySensor(msg.nodeId, msg.childSensorId, msg.payload, this);
//        sensor->setState(true);
        m_sensors << sensor;
        emit sensorAdded(m_sensors.last());
        break;
    }
    case SensorArduinoNode:
        qDebug() << QString("Node %1 is a non-repeating Arduino node").arg(msg.nodeId).toLocal8Bit().data();
        break;
    default:
        qWarning() << "Node" << msg.nodeId << "presented Unknown type" << msg.type << ":" << msg;
    }
}

void Controller::handleSetMessage(const Message &msg)
{
    Sensor *sensor = findSensor(msg.nodeId, msg.childSensorId);
    if(sensor) {
        sensor->handleMessage(msg);
    } else {
        qWarning() << "Unhandled set message for Node" << msg.nodeId << "Sensor" << msg.childSensorId;
    }
}

void Controller::handleInternalMessage(const Message &msg)
{
    switch(msg.type)
    {
    case InternalGatewayReady:
        qDebug() << "Found gateway:" << msg.payload;
        break;
    default:
        qWarning() << "Unknown internal message of type" << msg.type << ":" << msg;
    }
}

Sensor *Controller::findSensor(int nodeId, int sensorId)
{
    foreach(Sensor *sensor, m_sensors) {
        if(sensor->nodeId() == nodeId && sensor->sensorId() == sensorId) {
            return sensor;
        }
    }

    return nullptr;
}
