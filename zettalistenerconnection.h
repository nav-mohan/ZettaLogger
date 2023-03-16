#if !defined(ZETTALISTENERCONNECTION_H)
#define ZETTALISTENERCONNECTION_H

#include <QByteArray>
#include <QIODevice>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>

#define CONNECTIONTYPE_TCPSERVER 0;
#define CONNECTIONTYPE_SHAREDMEMORY 1;

class ZettaListenerConnection : public QIODevice {
Q_OBJECT

public:
    ZettaListenerConnection();
    ~ZettaListenerConnection();

    QTcpServer *m_tcpServer;// only one of these will be used at a time. 
    int m_messageQueueKey;// only one of these will be used at a time. 
    QByteArray *m_buffer;
    int m_connectionType;

protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);
};

#endif // ZETTALISTENERCONNECTION_H
