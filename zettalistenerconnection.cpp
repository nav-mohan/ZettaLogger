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





void ZettaListenerConnection::openConnection(int portOrKey)
{
    if(m_connectionType == CONNECTIONTYPE_SHAREDMEMORY)
    {
        accessSharedMemory(portOrKey);
        qDebug("Opening SharedMemory: %d",portOrKey);
    }
    if(m_connectionType == CONNECTIONTYPE_TCPSERVER)
    {
        establishTcpServer(portOrKey);
        qDebug("Opening Port: %d",portOrKey);
    }
    
    m_connectionStatus = 1;
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



void ZettaListenerConnection::establishTcpServer(int portOrKey)
{

    qDebug("Opening Port %d...",portOrKey);
    m_tcpServer = new QTcpServer();
    if(m_tcpServer->listen(QHostAddress::Any, portOrKey))
        qDebug("LISTENING...");

}

void ZettaListenerConnection::accessSharedMemory(int portOrKey)
{
    key_t key = ftok("shmfile",portOrKey);
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096,0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);
  
    qDebug("Data read from memory: %s\n",str);
      
    //detach from shared memory 
    shmdt(str);
    
    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);
}
