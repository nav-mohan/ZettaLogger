#if !defined(HTTPSERVER_H)
#define HTTPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QString>
#include<QByteArray>
#include <QDataStream>
#include <string>
#include <QRegularExpression>
#include <QDateTime>

class HttpServer : public QObject {
Q_OBJECT
public:
    HttpServer();
    ~HttpServer();

    void initialize(int portNumber);
    void close();
    void appendToSocketList(QTcpSocket *socket);

public slots:
    void newConnection();
    void readSocket();
    void deleteSocket();

private:
    QTcpServer *m_tcpServer;
    QSet<QTcpSocket*> m_connectionSet;

signals:
    void connectionChanged(bool connectionStatus);
};

#endif // HTTPSERVER_H
