#include "zettalistenerconnection.h"


ZettaListenerConnection::ZettaListenerConnection()
{
    m_tcpServer = new QTcpServer();
}

ZettaListenerConnection::~ZettaListenerConnection()
{
    m_tcpServer->deleteLater();
    delete m_buffer;
}

qint64 ZettaListenerConnection::readData(char *data, qint64 maxSize)
{
    return maxSize;
}
qint64 ZettaListenerConnection::writeData(const char *data, qint64 maxSize)
{
    return maxSize;
}
