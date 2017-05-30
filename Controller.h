#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:

public slots:
    void connected();
    void disconnected();
    void showError(QAbstractSocket::SocketError err);
    void connectToHost(QString host, int port);

private:
    QTcpSocket *tcpSocket;
};

#endif // CONTROLLER_H
