#include <QByteArray>
#include <QIODevice>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>

class ZettaListenerConnection : public QIODevice {
Q_OBJECT

public:
    ZettaListenerConnection();
    ~ZettaListenerConnection();

private:
    QTcpServer *m_tcpServer;// only one of these will be used at a time. 
    int m_messageQueueKey;// only one of these will be used at a time. 
    QByteArray *m_buffer;

};