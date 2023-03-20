#if !defined(ZETTALISTENERCONNECTION_H)
#define ZETTALISTENERCONNECTION_H

#include <QByteArray>
#include <QIODevice>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QSharedMemory>


#define CONNECTIONTYPE_NONE -1
#define CONNECTIONTYPE_TCPSERVER 0
#define CONNECTIONTYPE_SHAREDMEMORY 1

class ZettaListenerConnection : public QIODevice {
Q_OBJECT

public:
    ZettaListenerConnection();
    ~ZettaListenerConnection();

    QTcpServer *m_tcpServer;// the tcp server will at the very least be used for receiving readyRead signals. 
    QSharedMemory *m_sharedMemory;
    QByteArray *m_buffer;
    int m_connectionType;
    int m_connectionStatus;

public slots:
    void changeConnectionType(int);
    void openConnection(int);
    void closeConnection();

private slots:
    void openTcpServer(int port);
    void closeTcpServer();

signals:
    void signalMessage(QString,QString);
    void connectionChanged(bool,int);

protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);

private:
    int m_tcpPortNumber;
};

#endif // ZETTALISTENERCONNECTION_H
