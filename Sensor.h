#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Controller;
struct Message;

class Sensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int nodeId MEMBER m_nodeId)
    Q_PROPERTY(int sensorId MEMBER m_sensorId)
    Q_PROPERTY(int type MEMBER m_type)
    Q_PROPERTY(QString name MEMBER m_name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Sensor(Controller *parent = 0);
    explicit Sensor(int nodeId, int sensorId, int type, QString name, Controller *parent = 0);

    QString name() const;
    void setName(const QString &name);

    int nodeId() const;
    void setNodeId(int nodeId);

    int sensorId() const;
    void setSensorId(int sensorId);

    // Virtual member functions
    virtual void handleMessage(const Message &msg) {}

signals:
    void nameChanged(QString name);

protected:
    Controller *m_controller;

    int     m_nodeId;
    int     m_sensorId;
    int     m_type;
    QString m_name;
};

#endif // SENSOR_H
