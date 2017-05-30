#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;
struct Message;

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList messageLog MEMBER m_messageLog NOTIFY messageLogChanged)
public:
    explicit Controller(QObject *parent = 0);

    ~Controller();

signals:
    void messageLogChanged();

public slots:
    void read();
    void connected();
    void disconnected();
    void showError(QAbstractSocket::SocketError err);
    void connectToHost(QString host, int port);

private:
    QTcpSocket *tcpSocket;
    QStringList m_messageLog;
};

#endif // CONTROLLER_H
