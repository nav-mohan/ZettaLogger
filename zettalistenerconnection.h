#if !defined(ZETTALISTENERCONNECTION_H)
#define ZETTALISTENERCONNECTION_H

#include <QByteArray>
#include <QIODevice>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QSharedMemory>
#include <QSet>
#include <QDateTime>
#include <QMap>
#include <QDataStream>

#define CONNECTIONTYPE_TCPSERVER 0
#define CONNECTIONTYPE_SHAREDMEMORY 1

class ZettaListenerConnection : public QObject {
Q_OBJECT

public:
    ZettaListenerConnection();
    ~ZettaListenerConnection();

    QTcpServer *m_tcpServer;// the tcp server will at the very least be used for receiving readyRead signals. 
    QSharedMemory *m_sharedMemory;
    QByteArray m_buffer;
    int m_connectionType;
    int m_connectionStatus;
    int m_tcpPortNumber;
    QSet<QTcpSocket*> m_connectionSet;

public slots:
    void changeConnectionType(int);
    void newConnection();
    void closeTcpServer();
    void establishTcpServer(int port);

private slots:
    void appendToSocketList(QTcpSocket *socket);
    void readSocket();
    void deleteSocket();

signals:
    void signalMessage(QString,QString);
    void connectionChanged(bool,int);
    void dataReady(QMap<QString,QString>);
    void appendLog(const QString &str);
    void alert(const QString& windowTitle, const QString &windowInfo);
    void insertRecord(QMap<QString,QString>&map);
};

#endif // ZETTALISTENERCONNECTION_H
