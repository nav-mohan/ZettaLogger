#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : 
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_databaseConnection(new DatabaseConnection()),
    m_zettaListenerConnection(new ZettaListenerConnection()),
    m_httpServer(new HttpServer())
{
    m_ui->setupUi(this);
    m_ui->sharedMemoryKeyValue->setReadOnly(true);
    m_ui->sharedMemoryKeyValue->setPlaceholderText("N/A");
    connect(m_databaseConnection,&DatabaseConnection::signalMessage,this,&MainWindow::displayMessage);
    connect(m_databaseConnection,&DatabaseConnection::connectionChanged,this,&MainWindow::databaseConnectionChanged);
    m_ui->comboBox_connectionType->setPlaceholderText("ZettaListener Connection Type");
    connect(m_zettaListenerConnection,&ZettaListenerConnection::signalMessage,this,&MainWindow::displayMessage);
    connect(m_zettaListenerConnection,&ZettaListenerConnection::connectionChanged,this,&MainWindow::zettaListenerConnectionChanged);
    m_ui->plainTextEdit_receivedLogs->setReadOnly(true);
    m_ui->plainTextEdit_receivedLogs->setPlaceholderText("Received Logs:\n");
    // m_ui->plainTextEdit_receivedLogs->insertPlainText("Received Logs:\n");
}


void MainWindow::on_pushButton_clearLogs_clicked()
{
    m_ui->plainTextEdit_receivedLogs->setPlainText("");
}


void MainWindow::databaseConnectionChanged(bool connectionStatus)
{
    m_databaseConnectionStatus = connectionStatus;
    m_ui->databaseUrlValue->setReadOnly(m_databaseConnectionStatus);
    m_ui->databaseNameValue->setReadOnly(m_databaseConnectionStatus);
    m_ui->databaseUsernameValue->setReadOnly(m_databaseConnectionStatus);
    m_ui->databasePasswordValue->setReadOnly(m_databaseConnectionStatus);

    if(m_databaseConnectionStatus)
    {
        m_ui->pushButton_connectDatabase->setText("Disconnect from Database");
    }
    else
    {
        m_ui->pushButton_connectDatabase->setText("Connect to Database");
    }
}

void MainWindow::zettaListenerConnectionChanged(bool connectionStatus, int connectionType)
{
    qDebug("ZETTALISTENER CONNECTION CHANGED! %d | %d",connectionStatus,connectionType);
    m_zettaListenerConnectionStatus = connectionStatus;
    m_ui->comboBox_connectionType->setDisabled(m_zettaListenerConnectionStatus);
    m_ui->portNumberValue->setReadOnly(m_zettaListenerConnectionStatus);

    if(m_zettaListenerConnectionStatus)
    {
        m_ui->pushButton_connectZettaListener->setText("Disconnect from ZettaListener");
    }
    else
    {
        m_ui->pushButton_connectZettaListener->setText("Connect to ZettaListener");
    }

}

MainWindow::~MainWindow()
{
    if(m_zettaListenerConnection){
        delete m_zettaListenerConnection;
    }
}
void MainWindow::on_pushButton_connectDatabase_clicked()
{
    std::string databaseUrl         = m_ui->databaseUrlValue->text().toStdString();
    std::string databaseName        = m_ui->databaseNameValue->text().toStdString();
    std::string databaseUsername    = m_ui->databaseUsernameValue->text().toStdString();
    std::string databasePassword    = m_ui->databasePasswordValue->text().toStdString();
    
    qDebug() << databaseUrl.c_str() << databaseName.c_str() << databaseUsername.c_str() << databasePassword.c_str();

    m_databaseConnection->setAuthentication(databaseUrl, databaseUsername, databasePassword, databaseName);

}

void MainWindow::on_pushButton_connectZettaListener_clicked()
{
    int portNumber = m_ui->portNumberValue->text().toInt();
    if(!m_zettaListenerConnectionStatus)
        m_zettaListenerConnection->openConnection(portNumber);
    else
        m_zettaListenerConnection->closeConnection();
}

void MainWindow::on_comboBox_connectionType_currentIndexChanged(int connectionTypeIndex)
{
    m_zettaListenerConnection->changeConnectionType(connectionTypeIndex);
    if(connectionTypeIndex == CONNECTIONTYPE_SHAREDMEMORY)
    {
        m_ui->sharedMemoryKeyValue->setReadOnly(false);
        m_ui->sharedMemoryKeyValue->setPlaceholderText("Enter Unique String");

    }
    else if(connectionTypeIndex == CONNECTIONTYPE_TCPSERVER)
    {
        m_ui->sharedMemoryKeyValue->setReadOnly(true);
        m_ui->sharedMemoryKeyValue->setPlaceholderText("N/A");
    }
}

void MainWindow::readSocket()
{

}

void MainWindow::deleteSocket()
{

}

void MainWindow::displayMessage(QString windowTitle, QString windowInfo)
{
    // qDebug("%s",error.c_str());
    QMessageBox msgBox;
    msgBox.setWindowTitle(windowTitle);
    msgBox.setText(windowTitle);
    msgBox.setInformativeText(windowInfo);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();
}

void MainWindow::on_pushButton_startWebApi_clicked()
{
    int portNumber = m_ui->webApiPortValue->text().toInt();
    QString endpoint = m_ui->webApiEndpointValue->text();
    qDebug() << portNumber << endpoint;
    m_httpServer->initialize(portNumber);

}