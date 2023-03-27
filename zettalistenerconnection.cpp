#include "zettalistenerconnection.h"

ZettaListenerConnection::ZettaListenerConnection():
m_connectionStatus(false),
m_connectionType(CONNECTIONTYPE_TCPSERVER),
m_tcpServer(new QTcpServer())
{
    emit connectionChanged(m_connectionStatus,m_connectionType);
    qDebug("ZettaListenerConnection::ZettaListenerConnection %d,%d",m_connectionStatus,m_connectionType);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &ZettaListenerConnection::newConnection);
}

ZettaListenerConnection::~ZettaListenerConnection()
{
    // m_tcpServer->deleteLater();
    // delete m_buffer;
}

void ZettaListenerConnection::newConnection()
{
    qDebug() << "New connection detected!!";
    emit appendLog(QString("%1 :: New message stream arriving").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    while(m_tcpServer->hasPendingConnections())
        appendToSocketList(m_tcpServer->nextPendingConnection());
}

void ZettaListenerConnection::appendToSocketList(QTcpSocket *socket)
{
    m_connectionSet.insert(socket);
    connect(socket,&QTcpSocket::readyRead, this, &ZettaListenerConnection::readSocket);
    connect(socket,&QTcpSocket::disconnected, this, &ZettaListenerConnection::deleteSocket);
}

void ZettaListenerConnection::readSocket()
{
    qDebug() << "Reading " << sender();
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    int bytesAvailable = socket->bytesAvailable();
    QByteArray newData = socket->readAll();
    m_buffer.append(newData);
}

void ZettaListenerConnection::deleteSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = m_connectionSet.find(socket);
    if (it != m_connectionSet.end()){
        emit appendLog(QString("INFO :: A client has just left the room %1").arg(socket->socketDescriptor()));
        m_connectionSet.remove(*it);
    }
    qDebug() << "Deleting " << sender();
    QMap<QString,QString> map;
    QDataStream stream(&m_buffer, QIODevice::ReadOnly);
    stream >> map;
    socket->deleteLater();
    emit insertRecord(map);
    // doRegexMatch();
    m_buffer.clear();
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

void ZettaListenerConnection::establishTcpServer(int portNumber)
{
    if(m_tcpServer->listen(QHostAddress::Any, portNumber))
    {
        qDebug("LISTENING ON %d...",m_tcpServer->serverPort());
        m_tcpPortNumber = m_tcpServer->serverPort();
        m_connectionStatus = 1;
        emit connectionChanged(m_connectionStatus,m_connectionType);
    }
    else
    {
        emit appendLog("ZettaLogger Server closed");
    }
}

void ZettaListenerConnection::closeTcpServer()
{
    qDebug("CLOSING TCPSERVER");
    m_tcpServer->close();
    m_connectionStatus = 0;
    emit connectionChanged(m_connectionStatus,m_connectionType);
    emit appendLog("ZettaLogger Server closed");
    return;
}
