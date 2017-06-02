#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QAbstractSocket>
#include <QTimer>

class QTcpSocket;
struct Message;
class BinarySensor;

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList messageLog MEMBER m_messageLog NOTIFY messageLogChanged)
public:
    explicit Controller(QObject *parent = 0);

    ~Controller();

signals:
    void messageLogChanged();
    void connectionEstablished();
    void connectionLost();
    void sensorAdded(BinarySensor *sensor);

public slots:
    void read();
    void connected();
    void disconnected();
    void showError(QAbstractSocket::SocketError err);
    void connectToHost(QString host, int port);

private:
    void handleMessage(const Message &msg);
    void handlePresentationMessage(const Message &msg);
    void handleInternalMessage(const Message &msg);

    QTcpSocket  *tcpSocket;
    QStringList m_messageLog;
    QList<BinarySensor*> m_sensors;
};

#endif // CONTROLLER_H
