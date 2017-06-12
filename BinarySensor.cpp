#include "BinarySensor.h"
#include "Controller.h"
#include "MessageParser.h"

BinarySensor::BinarySensor(Controller *parent) : Sensor(parent) {}

BinarySensor::BinarySensor(int nodeId, int sensorId, QString name, Controller *parent)
    : Sensor(nodeId, sensorId, SensorBinary, name, parent)
    , m_state(false)
{

}

void BinarySensor::handleMessage(const Message &msg)
{
    switch(msg.type)
    {
    case DataStatus:
    {
        bool newState = msg.payload.toInt();
        if(newState != m_state) {
            m_state = newState;
            emit stateChanged(m_state);
        }
        break;
    }
//    case DataWatt:
    default:
        qWarning() << "BinarySensor: Cannot handle message of type" << msg.type;
    }
}

void BinarySensor::setState(bool on) {
    Message msg;
    msg.nodeId          = m_nodeId;
    msg.childSensorId   = m_sensorId;
    msg.command         = CommandSet;
    msg.ack             = false;
    msg.type            = DataStatus;
    msg.payload         = on ? "1" : "0";

    m_controller->send(msg);
    if(m_state != on) {
        m_state = on;
        emit stateChanged(m_state);
    }
}
