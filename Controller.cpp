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
    int read;
    char data[1024 * 8];
    data[0] = '\0';

    while((read = tcpSocket->readLine(data, 1024 * 8)) > 0)
    {
        handleMessage(MessageParser::parseMessage(data));
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

/// @brief The command field (message-type) defines the overall properties of a message
enum MessageCommand
{
    CommandPresentation     = 0,    //!< Sent by a node when they present attached sensors. This is usually done in presentation() at startup.
    CommandSet              = 1,    //!< This message is sent from or to a sensor when a sensor value should be updated.
    CommandRequest          = 2,    //!< Requests a variable value (usually from an actuator destined for controller).
    CommandInternal         = 3,    //!< Internal MySensors messages (also include common messages provided/generated by the library).
    CommandStream           = 4     //!< For firmware and other larger chunks of data that need to be divided into pieces.
};

enum MessageSensor
{
    SensorBinary            = 3,    //!< Binary light or relay, V_STATUS, V_WATT
    SensorArduinoNode       = 17    //!< Used (internally) for presenting a non-repeating Arduino node
};

enum MessageData
{
    DataStatus              = 2 	//!< S_BINARY, S_DIMMER, S_SPRINKLER, S_HVAC, S_HEATER. Used for setting/reporting binary (on/off) status. 1=on, 0=off
};

enum MessageInternal
{
    InternalGatewayReady    = 14    //!< Gateway ready
};

void Controller::handleMessage(const Message &msg)
{
    switch(msg.command)
    {
    case CommandPresentation:
        handlePresentationMessage(msg);
        break;
    case CommandInternal:
        handleInternalMessage(msg);
        break;
    default:
        qWarning() << "Unknown command type" << msg.command;
    }
}

void Controller::handlePresentationMessage(const Message &msg)
{
    switch(msg.type)
    {
    case SensorBinary:
        qDebug() << QString("Node %1 has Binary Sensor with ID %2").arg(msg.nodeId).arg(msg.childSensorId);
        break;
    case SensorArduinoNode:
        qDebug() << QString("Node %1 is a non-repeating Arduino node").arg(msg.nodeId);
        break;
    default:
        qWarning() << "Unknown presentation message of type" << msg.type;
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
        qWarning() << "Unknown internal message of type" << msg.type;
    }
}
