#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QAbstractSocket>
#include <QTimer>

class QTcpSocket;
struct Message;
class Sensor;

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList messageLog MEMBER m_messageLog NOTIFY messageLogChanged)
public:
    explicit Controller(QObject *parent = 0);

    ~Controller();

    void send(Message msg);


signals:
    void messageLogChanged();
    void connectionEstablished();
    void connectionLost();
    void sensorAdded(Sensor *sensor);

public slots:
    void read();
    void connected();
    void disconnected();
    void showError(QAbstractSocket::SocketError err);
    void connectToHost(QString host, int port);

private:
    void handleMessage(const Message &msg);
    void handlePresentationMessage(const Message &msg);
    void handleSetMessage(const Message &msg);
    void handleInternalMessage(const Message &msg);

    Sensor *findSensor(int nodeId, int sensorId);

    QTcpSocket  *tcpSocket;
    QStringList m_messageLog;
    QList<Sensor*> m_sensors;
};

#endif // CONTROLLER_H
