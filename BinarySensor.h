#ifndef BINARYSENSOR_H
#define BINARYSENSOR_H

#include "Sensor.h"

class BinarySensor : public Sensor
{
    Q_OBJECT
    Q_PROPERTY(bool state MEMBER m_state NOTIFY stateChanged)
public:
    explicit BinarySensor(Controller *parent = 0);
    explicit BinarySensor(int nodeId, int sensorId, QString name, Controller *parent = 0);

    void handleMessage(const Message &msg);

signals:
    void stateChanged(bool state);

public slots:
    void setState(bool on);

private:
    bool m_state;
};

#endif // BINARYSENSOR_H
