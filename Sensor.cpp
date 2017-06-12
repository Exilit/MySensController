#include "Sensor.h"
#include "Controller.h"
#include "MessageParser.h"

Sensor::Sensor(Controller *parent) : QObject(parent), m_controller(parent) {}

Sensor::Sensor(int nodeId, int sensorId, int type, QString name, Controller *parent)
    : QObject(parent)
    , m_controller(parent)
    , m_nodeId(nodeId)
    , m_sensorId(sensorId)
    , m_type(type)
    , m_name(name)
{

}

int Sensor::sensorId() const
{
    return m_sensorId;
}

void Sensor::setSensorId(int sensorId)
{
    m_sensorId = sensorId;
}

int Sensor::nodeId() const
{
    return m_nodeId;
}

void Sensor::setNodeId(int nodeId)
{
    m_nodeId = nodeId;
}

QString Sensor::name() const
{
    return m_name;
}

void Sensor::setName(const QString &name)
{
    if(m_name != name) {
        m_name = name;
        emit nameChanged(name);
    }
}
