#include "zettalistenerconnection.h"

ZettaListenerConnection::ZettaListenerConnection()
{
    m_connectionStatus = false;
    m_connectionType = CONNECTIONTYPE_TCPSERVER;
    emit connectionChanged(m_connectionStatus,m_connectionType);
    qDebug("ZettaListenerConnection::ZettaListenerConnection %d,%d",m_connectionStatus,m_connectionType);

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
    return;
}

void ZettaListenerConnection::closeConnection()
{
    closeTcpServer();
    m_connectionStatus = 0;
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
    qDebug("emitting on combobox change");
    emit connectionChanged(m_connectionStatus,m_connectionType);
    return;
}

void ZettaListenerConnection::openTcpServer(int portNumber)
{
    if(portNumber < 1000){
        emit signalMessage("WARNING",QString("Please choose a port number above 1000. You currently chose %1").arg(portNumber));
        return;
    }
    qDebug("Opening Port %d...",portNumber);
    m_tcpServer = new QTcpServer();
    if(m_tcpServer->listen(QHostAddress::Any, portNumber))
    {
        qDebug("LISTENING ON %d...",m_tcpServer->serverPort());
        m_tcpPortNumber = m_tcpServer->serverPort();
        m_connectionStatus = 1;
        emit connectionChanged(m_connectionStatus,m_connectionType);
    }

}

void ZettaListenerConnection::closeTcpServer()
{
    qDebug("CLOSING TCPSERVER");
    m_tcpServer->close();
}