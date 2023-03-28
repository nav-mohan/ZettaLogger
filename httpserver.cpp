#include "httpserver.h"

HttpServer::HttpServer()
{
    m_tcpServer = new QTcpServer();
    connect(m_tcpServer, &QTcpServer::newConnection, this, &HttpServer::newConnection);
}



HttpServer::~HttpServer()
{
    if(m_tcpServer)
    {
        m_tcpServer->close();
        emit connectionChanged(false);
        delete m_tcpServer;
    }
}

void HttpServer::close()
{
    emit connectionChanged(false);
    m_tcpServer->close();
}

void HttpServer::initialize(int portNumber)
{
    if(m_tcpServer->listen(QHostAddress::Any, portNumber))
    {
        qDebug("LISTENING...");
        emit connectionChanged(true);
    }
    else
    {
        qDebug("DISCONNECTED...");
        emit connectionChanged(false);
    }
}


void HttpServer::newConnection()
{
    qDebug() << "New connection!";
    while(m_tcpServer->hasPendingConnections())
        appendToSocketList(m_tcpServer->nextPendingConnection());
}


void HttpServer::appendToSocketList(QTcpSocket *socket)
{
    qDebug() << "Appending to list!";
    m_connectionSet.insert(socket);
    connect(socket,&QTcpSocket::readyRead, this, &HttpServer::readSocket);
    connect(socket,&QTcpSocket::disconnected, this, &HttpServer::deleteSocket);
}

void HttpServer::readSocket()
{
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    qDebug() << "HttpServer::readSocket " << socket;
    int bytesAvailable = socket->bytesAvailable();
    QByteArray newData = socket->readAll();
    // qDebug() << newData;
    QString dateString = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QRegularExpression re("GET /(\\d\\d\\d\\d\\-\\d\\d\\-\\d\\d)");
    QRegularExpressionMatch match = re.match(newData.mid(0,15));
    if(match.hasMatch())
        dateString = match.captured(1);
    qDebug() << dateString;
    emit readRecord(socket, dateString);
}

void HttpServer::deliverRecord(QTcpSocket *socket, QString record)
{
    qDebug() << "HttpServer::deliverRecord " << socket << record;
    QString response = "";
    response += "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html; charset=UTF-8\r\n";
    response += "Expires: Wed, 11 Jan 1984 05:00:00 GMT\r\n";
    response += "Transfer-Encoding: Identity\r\n";
    response += "Date: Tue, 21 Mar 2023 04:36:28 GMT\r\n";
    response += "Cache-Control: no-cache, must-revalidate, max-age=0\r\n";
    response += "Connection: keep-alive\r\n";
    response += "Server: nginx/1.18.0 (Ubuntu)\r\n";
    response += "\r\n";
    // response += "<html>\n";
    // response += "<body>" + record + "</body>\n";
    response += record + "\n";
    // response += "</html>\n";
    socket->write(response.toStdString().c_str());
    socket->disconnectFromHost();
}

void HttpServer::deleteSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    qDebug() << "HttpServer::deleteSocket " << socket;
    QSet<QTcpSocket*>::iterator it = m_connectionSet.find(socket);
    if (it != m_connectionSet.end()){
        qDebug() << (QString("INFO :: A client has just left the room %1").arg(socket->socketDescriptor()));
        m_connectionSet.remove(*it);
    }
    socket->deleteLater();
}