#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : 
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_databaseConnection(new DatabaseConnection()),
    m_zettaListenerConnection(new ZettaListenerConnection())
{
    m_ui->setupUi(this);
    connect(m_databaseConnection,&DatabaseConnection::signalMessage,this,&MainWindow::displayMessage);
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

}

void MainWindow::on_comboBox_connectionType_currentIndexChanged(int connectionTypeIndex)
{
    if(connectionTypeIndex == 0)
        m_ui->portSharedMemoryKeyLabel->setText("TCP Server Port");
    if(connectionTypeIndex == 1)
        m_ui->portSharedMemoryKeyLabel->setText("Shared Memory Key");
}


void MainWindow::readSocket()
{

}

void MainWindow::deleteSocket()
{

}

void MainWindow::setMessageQueueKey(int key)
{
    m_zettaListenerConnection->m_messageQueueKey = key;
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