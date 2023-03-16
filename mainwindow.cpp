#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : 
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_databaseConnection(new DatabaseConnection()),
    m_zettaListenerConnection(new ZettaListenerConnection())
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(m_zettaListenerConnection){
        delete m_zettaListenerConnection;
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
    m_zettaListenerConnection->m_messageQueueKey = key;
}