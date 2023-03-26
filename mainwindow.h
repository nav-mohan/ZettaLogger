#if !defined(MAINWINDOW_H)
#define MAINWINDOW_H

#include <QDebug>
#include <QDateTime>
#include <QMainWindow>

#include "zettalistenerconnection.h"
#include "databaseconnection.h"
#include "httpserver.h"
#include "dbcon.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_clearLogs_clicked();
    void on_pushButton_connectDatabase_clicked();
    void on_pushButton_connectZettaListener_clicked();
    void on_comboBox_connectionType_currentIndexChanged(int);
    void on_pushButton_startWebApi_clicked();
    void readSocket();
    void deleteSocket();
    void displayMessage(QString windowTitle, QString windowInfo);
    void zettaListenerConnectionChanged(bool,int);
    void databaseConnectionChanged(bool);
    void httpServerConnectionChanged(bool);
    
#ifdef IS_TESTING
public:
#else
private:
#endif
    Ui::MainWindow *m_ui;
    DatabaseConnection *m_databaseConnection;
    ZettaListenerConnection *m_zettaListenerConnection;
    HttpServer *m_httpServer;
    DbCon *m_dbCon;
    int m_zettaListernConnectionType;
    bool m_zettaListenerConnectionStatus;
    bool m_databaseConnectionStatus;
    bool m_httpServerConnectionStatus;
};

#endif // MAINWINDOW_H
