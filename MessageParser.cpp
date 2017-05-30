#include "MessageParser.h"

#include <QRegularExpression>
#include <QDebug>
MessageParser::MessageParser()
{

}

Message MessageParser::parseMessage(const QString &data)
{
    Message msg;
    QRegularExpression regex("(\\d+);(\\d+);(\\d+);(\\d+);(\\d+);([^\\n]*)\\n");

    QRegularExpressionMatch match = regex.match(data);

    if(match.hasMatch())
    {
        msg.nodeId          = match.captured(1).toInt();
        msg.childSensorId   = match.captured(2).toInt();
        msg.command         = match.captured(3).toInt();
        msg.ack             = match.captured(4).toInt();
        msg.type            = match.captured(5).toInt();
        msg.payload         = match.captured(6);
    }
    else
    {
        msg.nodeId = -1;
    }

    return msg;
}
