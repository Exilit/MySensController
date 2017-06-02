#ifndef BINARYSENSOR_H
#define BINARYSENSOR_H

#include <QObject>

class BinarySensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int nodeId MEMBER m_nodeId)
    Q_PROPERTY(int sensorId MEMBER m_sensorId)
    Q_PROPERTY(int type MEMBER m_type)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(bool state MEMBER m_state NOTIFY stateChanged)

public:
    explicit BinarySensor(QObject *parent = 0);
    explicit BinarySensor(int nodeId, int sensorId, int type, QString name, QObject *parent = 0);

signals:
    void stateChanged(bool state);

public slots:
    void setState(bool on);

private:
    int m_nodeId;
    int m_sensorId;
    int m_type;
    QString m_name;
    bool m_state;
};

#endif // BINARYSENSOR_H
