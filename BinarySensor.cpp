#include "BinarySensor.h"

BinarySensor::BinarySensor(QObject *parent) : QObject(parent) {}

BinarySensor::BinarySensor(int nodeId, int sensorId, int type, QString name, QObject *parent)
    : QObject(parent)
    , m_nodeId(nodeId)
    , m_sensorId(sensorId)
    , m_type(type)
    , m_name(name)
    , m_state(false)
{

}

void BinarySensor::setState(bool on) {
    m_state = on;
    emit stateChanged(m_state);
}
