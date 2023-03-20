#include "zettalistenerconnection.h"

ZettaListenerConnection::ZettaListenerConnection()
{
    m_connectionStatus = 0;
    m_connectionType = -1;
    emit connectionChanged(m_connectionStatus,m_connectionType);

}

ZettaListenerConnection::~ZettaListenerConnection()
{
    // m_tcpServer->deleteLater();
    // delete m_buffer;
}


qint64 ZettaListenerConnection::readData(char *data, qint64 maxSize)
{
    return maxSize;
}

qint64 ZettaListenerConnection::writeData(const char *data, qint64 maxSize)
{
    return maxSize;
}





void ZettaListenerConnection::openConnection(int portNumber)
{
    openTcpServer(portNumber);
    m_connectionStatus = 1;
    emit connectionChanged(m_connectionStatus,m_connectionType);
    return;
}

void ZettaListenerConnection::closeConnection()
{
    closeTcpServer();
    m_connectionStatus = 0;
    m_connectionType = CONNECTIONTYPE_NONE;
    emit connectionChanged(m_connectionStatus,m_connectionType);
    return;
}

void ZettaListenerConnection::changeConnectionType(int connectionType)
{
    if(m_connectionStatus)
    {
        emit signalMessage("ZettaListener Connection Error","You must disconnect the existing connection with ZettaListener.");
        return;
    }
    m_connectionStatus = false;
    m_connectionType = connectionType;
    emit connectionChanged(m_connectionStatus,m_connectionType);
    return;
}

void ZettaListenerConnection::openTcpServer(int portNumber)
{
    qDebug("Opening Port %d...",portNumber);
    m_tcpServer = new QTcpServer();
    if(m_tcpServer->listen(QHostAddress::Any, portNumber))
        qDebug("LISTENING...");

}

void ZettaListenerConnection::closeTcpServer()
{
    qDebug("CLOSING TCPSERVER");
    m_tcpServer->close();
}