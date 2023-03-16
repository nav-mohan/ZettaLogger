#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),m_ui(new Ui::MainWindow),m_databaseConnection(new DatabaseConnection())
{
    m_ui->setupUi(this);
    m_tcpSocket = new QTcpSocket();
    m_tcpSocket->open(QIODevice::ReadOnly);
}

MainWindow::~MainWindow()
{
    if(m_tcpSocket && m_tcpSocket->isOpen()){
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
    }
}

void MainWindow::on_pushButton_connectZettaListener_clicked()
{

}

void MainWindow::on_pushButton_connectDatabase_clicked()
{

}

void MainWindow::readSocket()
{

}

void MainWindow::deleteSocket()
{

}

void MainWindow::setMessageQueueKey(int key)
{
    m_messageQueueKey = key;
}