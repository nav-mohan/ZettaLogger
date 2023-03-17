#if !defined(ZETTALISTENERCONNECTION_H)
#define ZETTALISTENERCONNECTION_H

#include <QByteArray>
#include <QIODevice>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>

#include <sys/ipc.h>
#include <sys/shm.h>

#define CONNECTIONTYPE_NONE -1
#define CONNECTIONTYPE_TCPSERVER 0
#define CONNECTIONTYPE_SHAREDMEMORY 1

class ZettaListenerConnection : public QIODevice {
Q_OBJECT

public:
    ZettaListenerConnection();
    ~ZettaListenerConnection();

    QTcpServer *m_tcpServer;// only one of these will be used at a time. 
    int m_messageQueueKey;// only one of these will be used at a time. 
    QByteArray *m_buffer;
    int m_connectionType;
    int m_connectionStatus;

public slots:
    void changeConnectionType(int);
    void openConnection(int);

private slots:
    void establishTcpServer(int port);
    void accessSharedMemory(int key);

signals:
    void signalMessage(QString,QString);
    void connectionChanged(bool,int);

protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);
};

#endif // ZETTALISTENERCONNECTION_H
