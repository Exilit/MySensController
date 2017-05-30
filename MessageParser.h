#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QString>

struct Message
{
    int     nodeId;
    int     childSensorId;
    int     command;
    bool    ack;
    int     type;
    QString payload;

    operator QString() const { return QString("%1:%2 %3 %4 %5 '%6'")
                                        .arg(nodeId)
                                        .arg(childSensorId)
                                        .arg(command)
                                        .arg(ack)
                                        .arg(type)
                                        .arg(payload); }
};

class MessageParser
{
public:
    MessageParser();

    static Message parseMessage(const QString &data);
};

#endif // MESSAGEPARSER_H
